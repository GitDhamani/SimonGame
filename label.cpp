#include "label.h"
#include <QDebug>
#include <QTimer>

Label::Label(QWidget* parent, QString Colour, int id) : QLabel(parent), colour(Colour), Id(id)
{
    setAutoFillBackground(true);
    setStyleSheet("background-color: " + colour + "; border: 3px solid #000000; border-radius: 10px;");
    setFixedSize(90,90);

    delay = new QTimer(this);
    delay->setInterval(300);
    delay->setSingleShot(true);
    seqCount = 0;
}

void Label::mousePressEvent(QMouseEvent *event)
{
    if (colour == "#00aa00") //green
    setStyleSheet("background-color: #00e600; border: 3px solid #000000; border-radius: 10px;");
    if (colour == "#c80000") //red
    setStyleSheet("background-color: #ff6060; border: 3px solid #000000; border-radius: 10px;");
    if (colour == "#d6d600") //yellow
    setStyleSheet("background-color: #f5f700; border: 3px solid #000000; border-radius: 10px;");
    if (colour == "#0000c8") //blue
    setStyleSheet("background-color: #0374ff; border: 3px solid #000000; border-radius: 10px;");
}

void Label::mouseReleaseEvent(QMouseEvent *event)
{
    setStyleSheet("background-color: " + colour + "; border: 3px solid #000000; border-radius: 10px;");
    emit pressed(Id);
}

void Label::glow(QVector<int> seq, int count)
{
    if (seq[count] != Id)
        return;

    if(Id == 1)
    setStyleSheet("background-color: #00e600; border: 3px solid #000000; border-radius: 10px;");
    if(Id == 2)
    setStyleSheet("background-color: #ff6060; border: 3px solid #000000; border-radius: 10px;");
    if(Id == 3)
    setStyleSheet("background-color: #f5f700; border: 3px solid #000000; border-radius: 10px;");
    if(Id == 4)
    setStyleSheet("background-color: #0374ff; border: 3px solid #000000; border-radius: 10px;");

    delay->start();

    connect(delay, &QTimer::timeout, [=](){
        if(Id == 1)
        setStyleSheet("background-color: #00aa00; border: 3px solid #000000; border-radius: 10px;");
        if(Id == 2)
        setStyleSheet("background-color: #c80000; border: 3px solid #000000; border-radius: 10px;");
        if(Id == 3)
        setStyleSheet("background-color: #d6d600; border: 3px solid #000000; border-radius: 10px;");
        if(Id == 4)
        setStyleSheet("background-color: #0000c8; border: 3px solid #000000; border-radius: 10px;");
    });
}
