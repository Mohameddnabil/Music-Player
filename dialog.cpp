#include "dialog.h"
#include "ui_dialog.h"
#include<QFile>
#include<QString>
#include"help.h"
#include"registration.h"
#include"repass.h"
#include<QDebug>
#include<QMessageBox>
bool alreadyreg=0; int usernumber2;
void login(QString username,QString password){
    QFile file("C:/Users/Moham/Documents/Music_player/login.txt");
    int help=0;
    QString line;
    QString usr,pas,test1;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
       qDebug()<<"Could not open file";
        return ;
    }
    QTextStream in(&file);

    while (!in.atEnd()) {
        line = in.readLine();
        help++;
               if(help%2==0)
               {
                   pas=line;
               }
               else
               {
                   usr=line;
               }
               if(usr==username&&pas==password)
               {   usernumber2=help/2;
                   alreadyreg=1;
                   break;
               }
           }
           if(alreadyreg==0){
            return ;
           }
           file.close();
           return ;
    }
void logged1_in(QString usq,QString pos){
  QFile file("C:/Users/Moham/Documents/Music_player/logged_in.txt");
  if(!file.open(QIODevice::WriteOnly| QIODevice::Text)){
      qDebug()<<"Could not open file";
      return;
  }
   QTextStream out(&file);
   out << usq<<endl<<pos<<endl<<usernumber2;
   file.flush();
   file.close();
}
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Dialog::setFixedSize(QSize(753,537));
    ui->lineEdit->setPlaceholderText("Enter username");
    ui->lineEdit_2->setPlaceholderText("Enter password");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString username,password;
    username=ui->lineEdit->text();
    password=ui->lineEdit_2->text();
    login(username,password);
    logged1_in(username,password);
   if(alreadyreg==0)
   QMessageBox::critical(this,"Login error", "Incorrect username or password.");
           else {
       this->close();
       QMessageBox::information(this,"FYI","To rate any song you should select the title of the song");
           HELP* ho=new HELP;
           ho->setWindowTitle("MXA_Crusher_Music_Player :')");
           ho->show();
           }
  alreadyreg=0;
  }
void Dialog::on_checkBox_stateChanged(int arg1)
{
ui->lineEdit_2->setEchoMode(ui->checkBox->checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password );

}

void Dialog::on_pushButton_2_clicked()
{
    this->close();
    Registration q;
    q.setModal(true);
    q.exec();
}

void Dialog::on_pushButton_3_clicked()
{
    this->close();
    repass q;
    q.setModal(true);
    q.exec();
}
