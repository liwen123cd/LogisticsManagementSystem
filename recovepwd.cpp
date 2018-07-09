#include "recovepwd.h"
#include "ui_recovepwd.h"

RecovePwd::RecovePwd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecovePwd)
{
    ui->setupUi(this);
}

RecovePwd::~RecovePwd()
{
    delete ui;
}

void RecovePwd::on_pushButton_clicked()
{
    QString email = ui->lineEdit->text();
    if(email.length() == 0)
    {
        QMessageBox::information(this, "提示", "未填写邮箱！");
    }
    else
    {
        QMessageBox::information(this, "提示", "发送成功！"
                                             "请按提示步骤找回密码！");
    }
}

void RecovePwd::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
}
