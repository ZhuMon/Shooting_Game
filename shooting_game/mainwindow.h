#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>

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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    Player *player;
    Enemy *enemy;
    QTimer *timer;   //every timeout up
    QTimer *timerRF; //every timeout shoot one//Rapid Fire


};

#endif // MAINWINDOW_H
