#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QVBoxLayout>

#include "bullet.h"
#include "player.h"
#include "enemy.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);


private slots:
    void on_rapid_fire_clicked();

    void checkHP();

    void hit(Bullet *b);

    void on_start_clicked();

    void enemy_shoot();

    void on_stop_clicked();

    void enemy_move();

    void bullet_track_control();

    void on_pause_clicked();

signals:
    void bullet_track(int x, int y);


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    Character *player;
    Character *enemy;
    QTimer *timer;   //every timeout up
    QTimer *timerRF; //every timeout shoot one//Rapid Fire
    QTimer *timerES; //every timeout shoot one//Enemy Shoot

    //QVBoxLayout *levelmode;
    void setLevelMode();

    QAction *levelAction;
    QAction *playAction;
    void tolevelMode();
    void toplayMode();

    int enemy_move_cycle;
    int bullet_move_cycle;

    bool stopState;
};

#endif // MAINWINDOW_H
