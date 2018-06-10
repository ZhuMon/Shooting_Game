#ifndef LEVELBUTTON_H
#define LEVELBUTTON_H
#include <QPushButton>
#include <QObject>

class LevelButton :  public QPushButton
{
    Q_OBJECT
public:
    LevelButton(int level, QWidget *parent);

public slots:
    void MyClicked();

signals:
    void MyClick(int level);

private:
    int level;
};

#endif // LEVELBUTTON_H
