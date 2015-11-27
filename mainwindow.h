#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMediaPlayer>
#include<QPixmap>
#include<QIcon>
#include<iostream>
#include<QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void music_play();
    void music_stop();
    void positionChanged(qint64);
    void song_time(qint64);
    void positionMove(int);
    void load_local_music();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QUrl music_url;
    QPixmap *play_icon;
    bool ok;
    void init_ui();
    QPixmap *music_icon;
};

#endif // MAINWINDOW_H
