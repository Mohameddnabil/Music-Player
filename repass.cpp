#include "repass.h"
#include "ui_repass.h"
#include<QMessageBox>
#include"repass_continue.h"
#include<QFile>
#include<QDebug>
int usernumber4;
void write(int user){
    QFile file("C:/Users/Moham/Documents/Music_player/logged_in.txt");
    if(!file.open(QIODevice::WriteOnly| QIODevice::Text)){
        qDebug()<<"Could not open file";
        return;
    }
     QTextStream out(&file);
     QString line=out.readLine();
     out<<user;
     file.flush();
     file.close();
}
bool founded(QString email,QString code){
    QString founded1,founded2,line;
 QFile file("C:/Users/Moham/Documents/Music_player/emails.txt");
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
        qDebug()<<"Could not open file";
    }
    int help=0;
    QTextStream out(&file);
    while (!out.atEnd()) {
        line=out.readLine();
        help++;
        if(help%2!=0){founded1=line;}
        else{
            founded2=line;
            if(founded1==email&&founded2==code){
                usernumber4=help;
                file.flush();
                file.close();
                return  1;
            }
        }
    }
    file.flush();
    file.close();
    return 0;
}
repass::repass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::repass)
{
    ui->setupUi(this);
    ui->lineEdit_3->setPlaceholderText("Enter Email");
    ui->lineEdit_4->setPlaceholderText("Enter code");
    repass::setWindowTitle("MXA_Crusher_MUSIC_PLAYER :')");
}
repass::~repass()
{
    delete ui;
}
void repass::on_pushButton_clicked()
{
    QString email,code;
    email=ui->lineEdit_3->text();
    code=ui->lineEdit_4->text();
    if(founded(email,code)){
        write(usernumber4);
        this->close();
      repass_continue q;
      q.setModal(true);
      q.exec();
    }
    else{
        QMessageBox::critical(this,"Error","User doesn't exist");
    }
}

void repass::on_pushButton_2_clicked()
{
    this->close();
    Dialog q;
    q.setModal(true);
    q.exec();
}

