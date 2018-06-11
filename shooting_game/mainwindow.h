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
#include "levelbutton.h"

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
    void player_shoot();

    void checkHP();

    void hit(Bullet *b);

    void on_start_clicked();

    void enemy_shoot();

    void on_stop_clicked();

    void enemy_move();

    void bullet_track_control();

    void on_pause_clicked();

    void on_doubleshot_clicked();

    void check_skill_cd();

    void on_heal_clicked();

    void on_rapidfire_clicked();

    void level_choose(int level);

signals:
    void bullet_track(int x, int y, bool overPlus = false);


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
    int skill_cd_cycle;

    bool stopState;
    int doubleShotState; //0:one shot  1~5:two shot
    int rapidFireState;  //0:no 1~3:rapid

    int level;
    int passlevel;
};

#endif // MAINWINDOW_H
