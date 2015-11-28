#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     init_ui();
     setWindowTitle("CloudMusic");
     setWindowIcon(QIcon("images/cloudmusic.png"));
     setWindowFlags(Qt::FramelessWindowHint);
     setAttribute(Qt::WA_TranslucentBackground);//透明

     statue=3;
     connect(ui->play_BTN,SIGNAL(clicked(bool)),this,SLOT(music_play()));
     connect(ui->stop_BTN,SIGNAL(clicked(bool)),this,SLOT(music_stop()));
     connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(song_time(qint64)));
     connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
     connect(ui->time_Slider,SIGNAL(sliderMoved(int)),this,SLOT(positionMove(int)));
     connect(ui->load_action,SIGNAL(triggered(bool)),this,SLOT(load_local_music()));
     connect(ui->local_list,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(play_local_music()));
     connect(ui->next_BTN,SIGNAL(clicked(bool)),this,SLOT(next_music()));
     connect(ui->exit_action,SIGNAL(triggered(bool)),this,SLOT(close()));
     connect(player,SIGNAL(currentMediaChanged(QMediaContent)),this,SLOT(music_changed()));
     connect(ui->next_page_BTN,SIGNAL(clicked(bool)),this,SLOT(next_page()));
     connect(ui->last_page_BTN,SIGNAL(clicked(bool)),this,SLOT(last_page()));
     connect(ui->refesh_BTN,SIGNAL(clicked(bool)),this,SLOT(list_refresh()));

     label_list.append(ui->list_name_1);
     label_list.append(ui->list_name_2);
     label_list.append(ui->list_name_3);
     label_list.append(ui->list_name_4);
     label_list.append(ui->list_name_5);
     label_list.append(ui->list_name_6);
     label_list.append(ui->list_name_7);
     label_list.append(ui->list_name_8);
     label_list.append(ui->list_name_9);

     BTN_list.append(ui->list_play_1);
     BTN_list.append(ui->list_play_2);
     BTN_list.append(ui->list_play_3);
     BTN_list.append(ui->list_play_4);
     BTN_list.append(ui->list_play_5);
     BTN_list.append(ui->list_play_6);
     BTN_list.append(ui->list_play_7);
     BTN_list.append(ui->list_play_8);
     BTN_list.append(ui->list_play_9);

     image_btns.append(ui->image_1);
     image_btns.append(ui->image_2);
     image_btns.append(ui->image_3);
     image_btns.append(ui->image_4);
     image_btns.append(ui->image_5);
     image_btns.append(ui->image_6);
     image_btns.append(ui->image_7);
     image_btns.append(ui->image_8);
     image_btns.append(ui->image_9);

     page=0;
     net_statue=1;
     music_list_url="http://127.0.0.1:8000/musiclist/?page=";
     manager=new QNetworkAccessManager(this);
     manager->get(QNetworkRequest(QUrl(music_list_url+QString::number(page,10))));
     ui->last_page_BTN->setEnabled(false);
     id_list=new QStringList;
     connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(reply_finished(QNetworkReply*)));

     mkdir_temp();
     load_music_list();
}

void MainWindow::init_ui()
{
    play_icon=new QPixmap;
    music_icon=new QPixmap;
    music_icon->load("images/music_72.png");
    play_icon->load("images/Play_64.png");

    ui->play_BTN->setIconSize(QSize(play_icon->width()-15,play_icon->height()-18));
    ui->play_BTN->setIcon(QIcon("images/Play_64.png"));
    ui->next_BTN->setIcon(QIcon("images/Arrow_16.png"));
    ui->stop_BTN->setIcon(QIcon("images/Stop_24.png"));
    ui->refesh_BTN->setIcon(QIcon("images/Refresh_48.png"));
    ui->next_page_BTN->setIcon(QIcon("images/next_64.png"));
    ui->last_page_BTN->setIcon(QIcon("images/previous_64.png"));
    ui->list_play_1->setIcon(QIcon("images/Play_64.png"));
    ui->list_play_2->setIcon(QIcon("images/Play_64.png"));
    ui->list_play_3->setIcon(QIcon("images/Play_64.png"));
    ui->list_play_4->setIcon(QIcon("images/Play_64.png"));
    ui->list_play_5->setIcon(QIcon("images/Play_64.png"));
    ui->list_play_6->setIcon(QIcon("images/Play_64.png"));
    ui->list_play_7->setIcon(QIcon("images/Play_64.png"));
    ui->list_play_8->setIcon(QIcon("images/Play_64.png"));
    ui->list_play_9->setIcon(QIcon("images/Play_64.png"));
    ui->list_play_1->setFlat(true);
    ui->list_play_2->setFlat(true);
    ui->list_play_3->setFlat(true);
    ui->list_play_4->setFlat(true);
    ui->list_play_5->setFlat(true);
    ui->list_play_6->setFlat(true);
    ui->list_play_7->setFlat(true);
    ui->list_play_8->setFlat(true);
    ui->list_play_9->setFlat(true);
    ui->refesh_BTN->setFlat(true);
    ui->next_page_BTN->setFlat(true);
    ui->last_page_BTN->setFlat(true);
    ui->play_BTN->setFlat(true);
    ui->stop_BTN->setFlat(true);
    ui->next_BTN->setFlat(true);
    ok=true;

    ui->image_label->setScaledContents(true);
    ui->image_label->setPixmap(*music_icon);
    ui->song_name->setScaledContents(true);

    player=new QMediaPlayer(this);
    player->setMedia(music_url);

    ui->local_list->setFrameShape(QListWidget::NoFrame);
    ui->cloud_list->setFrameShape(QListWidget::NoFrame);

    local_play_list=new QMediaPlaylist;
    local_play_list->setPlaybackMode(QMediaPlaylist::Loop);
    cloud_play_list=new QMediaPlaylist;
    cloud_play_list->setPlaybackMode(QMediaPlaylist::Loop);
}

void MainWindow::music_play()
{
    if(ok)
    {
        player->play();
        ui->play_BTN->setIcon(QIcon("images/Pause_64.png"));
        ok=false;
    }
    else
    {
        player->pause();
        ok=true;
        ui->play_BTN->setIcon(QIcon("images/Play_64.png"));
    }
}

void MainWindow::music_stop()
{
    player->stop();
    ok=true;
    ui->play_BTN->setIcon(QIcon("images/Play_64.png"));
}

void MainWindow::positionChanged(qint64 position)
{
    ui->time_Slider->setValue(position);
}

void MainWindow::song_time(qint64 duration)
{
    ui->time_Slider->setRange(0,duration);
}

void MainWindow::positionMove(int position)
{
    player->setPosition(position);
}


void MainWindow::load_local_music()
{
    QString initialName=QDir::homePath();
    QStringList pathList=QFileDialog::getOpenFileNames(this, tr("选择文件"), initialName, tr("(*.mp3 *.wmv)"));
    for(int i=0;i<pathList.size();++i)
    {
        QString path=QDir::toNativeSeparators(pathList.at(i));
        if(!path.isEmpty())
        {
            local_play_list->addMedia(QUrl::fromLocalFile(path));
            QString fileName=path.split("/").last().split(".").first();
            QListWidgetItem *item=new QListWidgetItem(fileName);
            ui->local_list->addItem(item);
        }
    }
    save_music_list();
}

void MainWindow::play_local_music()
{
    player->setPlaylist(local_play_list);
    int index=ui->local_list->currentRow();
    local_play_list->setCurrentIndex(index);
    player->play();
    ui->play_BTN->setIcon(QIcon("images/Pause_64.png"));
    ok=false;
    statue=1;
    music_changed();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::next_music()
{
    if(statue==1)
    {
        int index=local_play_list->currentIndex();
        if((index+1)==local_play_list->mediaCount())
            index=-1;
        local_play_list->setCurrentIndex(++index);
        player->play();
        ui->play_BTN->setIcon(QIcon("images/Pause_64.png"));
        ok=false;
    }
    if(statue==2)
    {
        int index=cloud_play_list->currentIndex();
        if(++index==cloud_play_list->mediaCount())
            index=-1;
        cloud_play_list->setCurrentIndex(++index);
        player->play();
        ui->play_BTN->setIcon(QIcon("images/Pause_64.png"));
        ok=false;
    }
}

void MainWindow::music_changed()
{
    if(statue==1)
    {
        int index=local_play_list->currentIndex();
        QString name=ui->local_list->item(index)->text();
        ui->song_name->setText(name);
    }
    if(statue==2)
    {
        int index=cloud_play_list->currentIndex();
    }
}

void MainWindow::load_cloud_music()
{

}

void MainWindow::play_cloud_music()
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) {
        dragPos=event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton) {
        move(event->globalPos()-dragPos);
        event->accept();
    }
}

void MainWindow::load_music_list()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    if(!db.open())
    {
        return;
    }
    QSqlQuery query;
    query.exec("select * from local_list");
    while(query.next())
    {
        QListWidgetItem *item=new QListWidgetItem(query.value(0).toString());
        ui->local_list->addItem(item);
        local_play_list->addMedia(QUrl::fromLocalFile(query.value(1).toString()));
    }
    query.exec();
    db.close();
}

void MainWindow::save_music_list()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    if(!db.open())
    {
        return;
    }
    QSqlQuery query;
    query.exec("create table if not exists local_list (name TEXT,url TEXT primary key)");
    query.exec("create table if not exists cloud_list (name TEXT,url TEXT primary key)");
    query.exec("create table if not exists music_list (name TEXT,int code primary key)");
    for(int i=0;i<local_play_list->mediaCount();++i)
    {
        query.prepare("insert into local_list (name,url)""values(?,?)");
        QString name=ui->local_list->item(i)->text();
        QString url=local_play_list->media(i).canonicalUrl().path();
        query.addBindValue(name);
        query.addBindValue(url);
        query.exec();
    }
    db.close();
}

void MainWindow::reply_finished(QNetworkReply *reply)
{
    if(net_statue==2)
    {
        save_image(reply,"temp/"+reply->url().toString().split("/").last());
    }

    if(net_statue==1)
    {
        get_music_lists(QJsonDocument::fromJson(reply->readAll()));
    }
}
void MainWindow::save_image(QNetworkReply *reply,QString name)
{
    QPixmap *currentPicture = new QPixmap;
    currentPicture->loadFromData(reply->readAll());
    currentPicture->save(name);
}

void MainWindow::get_music_lists(QJsonDocument json_data)
{
    id_list->clear();
    image_names.clear();
    QVariantList data_list=json_data.toVariant().toList();
    int i=0;
    foreach(QVariant item,data_list)
    {
        QVariantMap item_map = item.toMap();
        id_list->append(item_map[QLatin1String("id")].toString());
        label_list[i]->setText(item_map[QLatin1String("name")].toString());
        cover_image_list.append(item_map[QLatin1String("image_url")].toString()+"?param=140y140");
        ++i;
    }
    net_statue=2;
    QDir *temp = new QDir;
    foreach (QString url, cover_image_list)
    {
        qDebug()<<url;
        QString image_name="temp/"+url.split("/").last();
        image_names.append(image_name);
        bool exist = temp->exists(image_name);
        if(!exist)
        {
            manager->get(QNetworkRequest(QUrl(url)));
        }
    }
}

void MainWindow::last_page()
{
    page+=1;
    net_statue=1;
    manager->get(QNetworkRequest(QUrl(music_list_url+QString::number(page,10))));
    if(page==0)
        ui->last_page_BTN->setEnabled(false);
}

void MainWindow::next_page()
{
    page+=1;
    net_statue=1;
    manager->get(QNetworkRequest(QUrl(music_list_url+QString::number(page,10))));
    ui->last_page_BTN->setEnabled(false);
}

void MainWindow::list_refresh()
{

}

void MainWindow::mkdir_temp()
{
        QDir *temp = new QDir;
        bool exist = temp->exists("temp");
        if(!exist)
        {
            temp->mkdir("temp");
        }
}
