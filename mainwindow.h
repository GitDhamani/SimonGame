#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void handlePress(int);
    void generateSequence();
    QVector<int> seq;
    int maxlength;
    bool armed;
    int seqCounter;
    int currentPos;
    void playSeq();
    int showlength;
    QTimer* glownext;
    QTimer* entry;
    QTimer* incorrect;

signals:
    void resetCircle();
    void glow(QVector<int> seq, int count);
};
#endif // MAINWINDOW_H
