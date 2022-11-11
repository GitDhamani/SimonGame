#ifndef CIRCLE_H
#define CIRCLE_H

#include <QLabel>
#include <QObject>

class Circle: public QLabel
{
    Q_OBJECT
public:
    Circle(QWidget* parent);
    void reset();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void start();
    void stop();

private:
    bool state;
};

#endif // CIRCLE_H
