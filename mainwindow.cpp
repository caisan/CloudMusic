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
     //setWindowOpacity(0.7);
     load_cloud_music();
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
