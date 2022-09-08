#include "registration.h"
#include "ui_registration.h"
#include<QString>
#include<QMessageBox>
#include <QRegExp>
#include<QFile>
#include<QDebug>
#include"help.h"
const int song_length=37; int usernumber=0;
void counter(){ QString line;
    QFile file("C:/Users/Moham/Documents/Music_player/login.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Could not open file";
        return;
   }
     QTextStream in(&file);
     while (!in.atEnd()) {line = in.readLine(); usernumber++;}
    file.flush();
    file.close();
    usernumber/=2;
}
void rate_intializer(){
  QFile file("C:/Users/Moham/Documents/Music_player/rate.txt");
  if(!file.open(QIODevice::Append | QIODevice::Text)){
      qDebug()<<"Could not open file";
      return;
 }
  QTextStream out(&file);
  for(int i=0;i<song_length;i++)
  out <<3.0<<"  "<<i<<endl;
  file.flush();
  file.close();
}
void user_register(QString username,QString password){
    QFile file("C:/Users/Moham/Documents/Music_player/login.txt");
    if(!file.open(QIODevice::Append | QIODevice::Text)){
        qDebug()<<"Could not open file";
        return;
   }
    QTextStream out(&file);
    out << username<<endl<<password<<endl;
    file.flush();
    file.close();
}
void emails(QString email,QString verify1){
    QFile file("C:/Users/Moham/Documents/Music_player/emails.txt");
    if(!file.open(QIODevice::Append | QIODevice::Text)){
        qDebug()<<"Could not open file";
        return;
    }
    QTextStream out(&file);
    out <<email<<endl<<verify1<<endl;
    file.flush();
    file.close();
}
void logged2_in(QString usq,QString pos){
  QFile file("C:/Users/Moham/Documents/Music_player/logged_in.txt");
  if(!file.open(QIODevice::WriteOnly| QIODevice::Text)){
      qDebug()<<"Could not open file";
      return;
  }
   QTextStream out(&file);
   out<<usq<<endl<<pos<<endl<<usernumber;
   file.flush();
   file.close();
}
bool checker(QString username){
  QFile file("C:/Users/Moham/Documents/Music_player/login.txt");
   if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Could not open file";
   }
    QTextStream out(&file);
    int i=0; QString line;
    while(!out.atEnd()){
        i++;line=out.readLine();
        if(i%2!=0&&line==username){
            return 1;
        }
    }
    file.flush();
    file.close();
    return  0;
}
Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Enter username");
    ui->lineEdit_2->setPlaceholderText("Enter Password");
    ui->lineEdit_3->setPlaceholderText("Enter Email");
    ui->lineEdit_4->setPlaceholderText("Enter Password");
     ui->lineEdit_5->setPlaceholderText("Verify your mail");
    Registration::setWindowTitle("MXA_Crusher_MUSIC_PLAYER :')");
    Registration::setFixedSize(QSize(550,900));
}
Registration::~Registration()
{
    delete ui;
}
void Registration::on_pushButton_clicked()
{     QString user,pass,email,userc,verify;
       user=ui->lineEdit->text();
       pass=ui->lineEdit_2->text();
       email=ui->lineEdit_3->text();
       userc=ui->lineEdit_4->text();
       verify=ui->lineEdit_5->text();
         if((user==""&&pass==""&&email=="")||(user==" "&&pass==" "&&email==" ")){
             QMessageBox::critical(this,"Registration Erorr", "Enter  username and password and email");
         }
         else if((user==""&&pass=="")||(user==" "&&pass==" ")){QMessageBox::critical(this,"Registration Erorr", "Enter username and password");}
         else if((user==""&&email=="")||(user==" "&&email==" ")){QMessageBox::critical(this,"Registration Erorr", "Enter username and email");}
         else if ((email==""&&pass=="")||(email==" "&&pass==" ")){QMessageBox::critical(this,"Registration Erorr", "Enter password and email");}
         else if(user==""){ QMessageBox::critical(this,"Registration Erorr", "Enter username");
         }
          else if(pass==""){ QMessageBox::critical(this,"Registration Erorr", "Enter password");
         }
          else if(email==""){ QMessageBox::critical(this,"Registration Erorr", " Enter email");
         }
       else{
            if( checker(user)){
            QMessageBox::critical(this,"Erorr","Username is exist change it");
            return;
            }
if(verify==""){QMessageBox::critical(this,"Erorr","verify your mail");
           return;
}
if (pass!=userc){QMessageBox::critical(this,"Error","Password confirm is not correct");
    return ;
}
if(pass.size()<8||pass.size()>16){QMessageBox::critical(this,"Watch out","Password must be 8 to 16");
    return;
}
if(!email.contains("@gmail.com")&&!email.contains("@yahoo.com")&&!email.contains("@hotmail.com")){
QMessageBox::critical(this,"Erorr","invalid email");
return;
}
 user_register(user,pass);
         counter();
       logged2_in(user,pass);
       emails(email,verify);
       rate_intializer();
         this->close();
       HELP*q=new HELP;
    q->setWindowTitle("MXA_Crusher_Music_Player :')");
   q->show();
               }
           }
void Registration::on_checkBox_stateChanged(int arg1)
{
 ui->lineEdit_2->setEchoMode(ui->checkBox->checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password );

}
void Registration::on_checkBox_2_stateChanged(int arg1)
{
    ui->lineEdit_4->setEchoMode(ui->checkBox_2->checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password );

}
void Registration::on_pushButton_2_clicked()
{
       this->close();
       Dialog q;
       q.setModal(true);
       q.exec();
}
