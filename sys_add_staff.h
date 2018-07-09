#ifndef SYS_ADD_STAFF_H
#define SYS_ADD_STAFF_H

#define STATUS_AT "在职"
#include <QDialog>
#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class Sys_Add_Staff;
}

class Sys_Add_Staff : public QDialog
{
    Q_OBJECT

public:
    explicit Sys_Add_Staff(QDialog *parent = 0);
    ~Sys_Add_Staff();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Sys_Add_Staff *ui;
    QString staff_filename;
};

#endif // SYS_ADD_STAFF_H
