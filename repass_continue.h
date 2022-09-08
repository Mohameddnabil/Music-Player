#ifndef REPASS_CONTINUE_H
#define REPASS_CONTINUE_H

#include <QDialog>
#include"repass.h"
namespace Ui {
class repass_continue;
}

class repass_continue : public QDialog
{
    Q_OBJECT

public:
    explicit repass_continue(QWidget *parent = nullptr);
    ~repass_continue();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::repass_continue *ui;
};

#endif // REPASS_CONTINUE_H
