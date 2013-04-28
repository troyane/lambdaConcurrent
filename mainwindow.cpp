#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dao.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSendQuery_clicked()
{
    // usaeg of database access
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
