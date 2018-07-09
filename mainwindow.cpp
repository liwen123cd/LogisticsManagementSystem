#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globaldata.h"
#include "usermanager.h"
#include "staffmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(0 == Data::is_admin)
    {
        ui->pushButton->setVisible(false);
        ui->pushButton_3->setVisible(false);
    }
    qDebug()<<User::name;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    UserManager *um = new UserManager;
//    this->hide();
    um->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    StaffManager *sm = new StaffManager;
    sm->show();
}
