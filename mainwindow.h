/*-------------------------------------------------
|  Author: Gerasymchuk Nazar
|  neval8.wordpress.com
\------------------------------------------------*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    void setGuiEnabled(bool enabled);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btnSendQuery_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
