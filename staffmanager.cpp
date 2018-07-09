#include "staffmanager.h"
#include "ui_staffmanager.h"
#include "sys_add_staff.h"
#include "sys_maintain_staff.h"
#include "sys_sqlite.h"

StaffManager::StaffManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaffManager)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("Sys_Staff");
    // 系统管理只能物流公司使用，即管理系统管理员
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("编号"));
    model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, tr("所在部门"));
    model->setHeaderData(3, Qt::Horizontal, tr("职位"));
    model->setHeaderData(4, Qt::Horizontal, tr("状态"));
    model->setHeaderData(5, Qt::Horizontal, tr("电话"));
    model->setHeaderData(6, Qt::Horizontal, tr("就职日期"));
    model->setHeaderData(7, Qt::Horizontal, tr("照片"));
    model->setHeaderData(8, Qt::Horizontal, tr("备注"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
    // ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    //    ui->tableView->set
    // tableview设置某列不可编辑 待完善
}

StaffManager::~StaffManager()
{
    delete ui;
}

void StaffManager::on_pushButton_clicked()
{
    Sys_Add_Staff *add_staff = new Sys_Add_Staff;
    add_staff->exec();
    model->select();
}

void StaffManager::on_pushButton_9_clicked()
{
    model->select();
}

/*
 *
 *
 * 维护员工的信息
 * 由于员工牵扯到离职等
 *
 * */
void StaffManager::on_pushButton_2_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    qDebug()<<curRow;
    if(-1 == curRow)
    {
        QMessageBox::warning(this, tr("提示"),
                             "请先选中一行！");
    }
    else
    {
        staff = new Staff;
        QSqlRecord record = model->record(curRow);
        for(int i = 0; i < 9; i++)
        {
            qDebug()<<record.value(i)<<endl;
        }
        staff->id = record.value(0).toString();
        staff->name = record.value(1).toString();
        staff->deperment = record.value(2).toString();
        staff->position = record.value(3).toString();
        staff->status = record.value(4).toString();
        staff->phone = record.value(5).toString();
        staff->date = record.value(6).toString();
        staff->image = record.value(7).toString();
        staff->description = record.value(8).toString();

        Sys_Maintain_Staff *sms = new Sys_Maintain_Staff;
        sms->exec();
    }
    model->select();
}

void StaffManager::on_pushButton_3_clicked()
{
    if(NULL == ui->tableView->currentIndex().data(0).toString())
    {
        QMessageBox::warning(this, tr("提示"),
                             "请输入需要修改的内容！");
        model->revertAll();
    }
    // 开始事务操作
    model->database().transaction();

    if(model->submitAll())
    {
        model->database().commit();
    }
    else
    {
        model->database().rollback();
        QMessageBox::warning(this, tr("警告"),
                             tr("数据库错误: %1")
                             .arg(model->lastError().text()));
    }
}

void StaffManager::on_pushButton_4_clicked()
{
    model->revertAll();
}

void StaffManager::on_pushButton_11_clicked()
{
    QString inputQuery = ui->lineEdit->text();
    if(NULL == inputQuery)
    {
        QMessageBox::warning(this, tr("提示"),
                             "请输入需要查询的内容！");
    }
    else
    {
        if(STAFF_ID == ui->comboBox->currentText())
        {

        }
        if(STAFF_NAME == ui->comboBox->currentText())
        {

        }
        if(STAFF_DEPENTMENT == ui->comboBox->currentText())
        {

        }
    }
}
