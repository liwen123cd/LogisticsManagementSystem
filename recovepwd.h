#ifndef RECOVEPWD_H
#define RECOVEPWD_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class RecovePwd;
}

class RecovePwd : public QWidget
{
    Q_OBJECT

public:
    explicit RecovePwd(QWidget *parent = 0);
    ~RecovePwd();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::RecovePwd *ui;
};

#endif // RECOVEPWD_H
