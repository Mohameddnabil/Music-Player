#ifndef REGISTRATION_H
#define REGISTRATION_H
#include <QDialog>
#include"dialog.h"
namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_2_clicked();

private:
    Ui::Registration *ui;
};
#endif // REGISTRATION_H
