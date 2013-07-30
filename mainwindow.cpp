#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dao.h"
#include "threaddao.h"
#include "sleeperthread.h"
#include "QProgressIndicator.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pi(new QProgressIndicator(this)),
    td(*pi)
{
    ui->setupUi(this);

    QVBoxLayout* vbl = new QVBoxLayout(ui->pushButton);
    vbl->addWidget(pi, 0, Qt::AlignCenter);

    td.start();
}

MainWindow::~MainWindow()
{
    td.stopThread();
    delete ui;
}


void MainWindow::on_btnSendQuery_clicked()
{
    // usage of database access
    QString query("SELECT * FROM table1");
    // prepare lambda "how to freeze" and "how to unfreeze"
    // specialized on GUI interaction
    func freeze = [this] (void)
    {
        qDebug() << " # in lambda \"freeze GUI\"";
        setGuiEnabled(false);
    };
    func unfreeze = [this] (void)
    {
        qDebug() << " # in lambda \"unfreeze GUI\"";
        setGuiEnabled(true);
    };

    DAO concreteDao;
    concreteDao.applyQuery(query, freeze, unfreeze);
}

void MainWindow::setGuiEnabled(bool enabled)
{
    ui->btnSendQuery->setEnabled(enabled);
    if (enabled)
    {
        ui->lblStatus->setText("Idle");
    } else {
        ui->lblStatus->setText("Working too long");
    }
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "\t in on_pushButton_clicked";
    int intValue = 0;

    td.callSync(
                // lambda goes here
                [this, &intValue] (void)
    {
        qDebug() << "\t in lambda";
        QString temp;
        for (int i=1; i<300; ++i)
        {
            temp.append(QString::number(i*i / (i+1), 'f', 1));
            SleeperThread::msSleep(10);
        }
        intValue = 42;
        qDebug() << "\t lambda ends" << temp;
    },
    *ui->pushButton);

    qDebug() << "After calling lambda: " << intValue;
    ui->pushButton->setText(QString::number(intValue));
}
