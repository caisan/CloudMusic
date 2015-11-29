#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMediaPlayer>
#include<QPixmap>
#include<QIcon>
#include<iostream>
#include<QFileDialog>
#include<QListWidget>
#include<QMediaPlaylist>
#include<QMouseEvent>
#include<QSql>
#include<QDebug>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QJsonDocument>
#include<QJsonArray>
#include<QVariantList>
#include<QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mkdir_temp();
    void save_image(QNetworkReply *reply,QString name);
    void load_image();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private slots:
    void music_play();
    void music_stop();
    void positionChanged(qint64);
    void song_time(qint64);
    void positionMove(int);
    void load_local_music();
    void play_local_music();
    void next_music();
    void music_changed();
    void load_cloud_music();
    void play_cloud_music();
    void load_music_list();
    void save_music_list();
    void get_music_lists(QJsonDocument);
    void next_page();
    void last_page();
    void reply_finished(QNetworkReply *);
    void list_refresh();
    void get_list_images();
    void list_play_pressed();
private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QUrl music_url;
    QPixmap *play_icon;
    bool ok;
    void init_ui();
    QPixmap *music_icon;
    QMediaPlaylist *local_play_list;
    QMediaPlaylist *cloud_play_list;
    int statue;

    QPoint dragPos;
    QNetworkAccessManager *manager;
    int page;
    QString music_list_url;
    int net_statue;

    QStringList *id_list;
    QList<QPushButton *> BTN_list,image_btns;
    QList<QLabel *> label_list;
    QStringList cover_image_list;
    QStringList image_names;
};

#endif // MAINWINDOW_H
