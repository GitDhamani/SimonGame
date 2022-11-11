#include "circle.h"

Circle::Circle(QWidget* parent): QLabel(parent)
{
    setPixmap(QPixmap(":/Images/play.png"));
    setScaledContents(true);
    setFixedSize(30,30);
    move(85,85);
    state = 0;
}

void Circle::reset()
{
    setPixmap(QPixmap(":/Images/play.png"));
    state = 0;
}

void Circle::mousePressEvent(QMouseEvent *event)
{
    if (!state)
    {
    setPixmap(QPixmap(":/Images/Lose.png"));
    state = 1;
    emit start();
    }
    else
    {
    setPixmap(QPixmap(":/Images/play.png"));
    state = 0;
    emit stop();
    }
}
