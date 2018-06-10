#include "levelbutton.h"


LevelButton::LevelButton(int level, QWidget *parent):
    QPushButton(parent)
{
    setText(QString::number(level));
    this->level = level;
    setFixedHeight(100);
    setFixedWidth(100);
}

void LevelButton::MyClicked(){
    emit MyClick(level);
}
