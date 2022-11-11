#ifndef LABEL_H
#define LABEL_H

#include <QObject>
#include <QLabel>

class Label: public QLabel
{
    Q_OBJECT

public:
    Label(QWidget* parent, QString colour, int Id);
    QString colour;
    int Id;
    void glow(QVector<int> seq, int count);

signals:
    void pressed(int);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QTimer* glowon;
    QTimer* delay;
    int seqCount;
};

#endif // LABEL_H
