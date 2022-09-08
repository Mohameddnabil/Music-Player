#ifndef REPASS_H
#define REPASS_H

#include <QDialog>
#include"dialog.h"
namespace Ui {
class repass;
}

class repass : public QDialog
{
    Q_OBJECT

public:
    explicit repass(QWidget *parent = nullptr);
    ~repass();

private slots:
    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::repass *ui;
};

#endif // REPASS_H
