#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "globaldata.h"

namespace Ui {
class StaffManager;
}

class StaffManager : public QWidget
{
    Q_OBJECT

public:
    explicit StaffManager(QWidget *parent = 0);
    ~StaffManager();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::StaffManager *ui;
    QSqlTableModel *model;
    Staff *staff;
};

#endif // STAFFMANAGER_H
