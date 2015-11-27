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
     connect(ui->play_BTN,SIGNAL(clicked(bool)),this,SLOT(music_play()));
     connect(ui->stop_BTN,SIGNAL(clicked(bool)),this,SLOT(music_stop()));
     connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(song_time(qint64)));
     connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
     connect(ui->time_Slider,SIGNAL(sliderMoved(int)),this,SLOT(positionMove(int)));
     connect(ui->load_action,SIGNAL(triggered(bool)),this,SLOT(load_local_music()));
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
    ui->play_BTN->setFlat(true);
    ui->stop_BTN->setFlat(true);
    ui->next_BTN->setFlat(true);
    ok=true;

    ui->image_label->setScaledContents(true);
    ui->image_label->setPixmap(*music_icon);

    music_url=QUrl("http://m2.music.126.net/QcyK3pXe29RfZkpVD8MaVw==/1066526278951718.mp3");
    player=new QMediaPlayer(this);
    player->setMedia(music_url);
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
    QStringList pathList=QFileDialog::getOpenFileNames(this, tr("选择文件"), initialName, tr(".mp3"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
