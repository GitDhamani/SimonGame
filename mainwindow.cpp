#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "label.h"
#include <QGridLayout>
//#include <QDebug>
#include "circle.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(200,200);
    ui->statusbar->hide();
    ui->menubar->hide();

    setWindowTitle("[0] Simon");
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    maxlength = 50;  //Set Max number of the Sequence Here.
    armed = false;
    seqCounter = 0;
    currentPos = 0;
    showlength = 1;
    glownext = new QTimer(this);
    glownext->setInterval(600);
    glownext->setSingleShot(true);

    entry = new QTimer(this);
    entry->setInterval(800);
    entry->setSingleShot(true);

    incorrect = new QTimer(this);
    incorrect->setInterval(450);

    Label* GreenBox = new Label(this,"#00aa00", 1);
    Label* RedBox = new Label(this, "#c80000", 2);
    Label* YellowBox = new Label(this, "#d6d600", 3);
    Label* BlueBox = new Label(this, "#0000c8", 4);

    QGridLayout* gLayout = new QGridLayout(central);
    gLayout->addWidget(GreenBox, 0,0);
    gLayout->addWidget(RedBox, 0,1);
    gLayout->addWidget(YellowBox, 1,0);
    gLayout->addWidget(BlueBox, 1,1);

    Circle* circle = new Circle(this);

    connect(GreenBox, &Label::pressed, this, &MainWindow::handlePress);
    connect(RedBox, &Label::pressed, this, &MainWindow::handlePress);
    connect(YellowBox, &Label::pressed, this, &MainWindow::handlePress);
    connect(BlueBox, &Label::pressed, this, &MainWindow::handlePress);

    connect(circle, &Circle::start, this, &MainWindow::generateSequence);
    connect(circle, &Circle::stop, this, [=]()
    { seq.clear(); armed = false; seqCounter = 0; currentPos = 0; showlength = 1;
    entry->stop(); glownext->stop(); });

    connect(this, &MainWindow::resetCircle, circle, &Circle::reset);
    connect(this, &MainWindow::glow, GreenBox, &Label::glow);
    connect(this, &MainWindow::glow, RedBox, &Label::glow);
    connect(this, &MainWindow::glow, YellowBox, &Label::glow);
    connect(this, &MainWindow::glow, BlueBox, &Label::glow);

    connect(glownext, &QTimer::timeout, [=](){ playSeq(); });
    connect(entry, &QTimer::timeout, [=](){ playSeq(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlePress(int num)
{
    if (!armed)
        return;

    if (num != seq[seqCounter])
    {
        incorrect->start();
        int flashcount = 0;
        armed = false;
        emit resetCircle();
        connect(incorrect, &QTimer::timeout, [=]()mutable{
            flashcount++;
            emit glow(seq, seqCounter);
            if (flashcount == 4)
            {
                incorrect->stop();
                seq.clear();
                armed = false;
                seqCounter = 0;
                showlength = 1;
            }
        });
        return;
    }

    seqCounter++;

    if (seqCounter == maxlength)
    {
    QMessageBox::information(this, "Congratulations",
                             "You Mastered " + QString::number(maxlength) + " Sequences.");
    seq.clear();
    armed = false;
    seqCounter = 0;
    emit resetCircle();
    showlength = 1;
    return;
    }

    if (seqCounter == showlength-1)
    {
        setWindowTitle("[" + QString::number(seqCounter) + "] Simon");
        entry->start();
    }
}

void MainWindow::generateSequence()
{
    int lastnum=0, num;
    for (int i = 0; i < maxlength; i++)
    {
        do
        {
        num = QRandomGenerator::global()->bounded(1, 5);
        } while (num == lastnum);
        seq << num;
        lastnum = num;
    }

    armed = true;
    seqCounter = 0;

    setWindowTitle("[0] Simon");
    entry->start();
}

void MainWindow::playSeq()
{
    if(currentPos < showlength)
    {
    armed = 0;
    emit glow(seq, currentPos++);
    glownext->start();
    }
    else
    {
        showlength++;
        currentPos = 0;
        seqCounter = 0;
        armed = 1;
    }
}

