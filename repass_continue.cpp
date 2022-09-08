#include "repass_continue.h"
#include "ui_repass_continue.h"
#include<QMessageBox>
#include<QVector>
#include"repass.h"
#include<QFile>
#include<QDebug>
int usernum;
QString newpass;
QVector<QString>vc;
void final(){
    QFile file("C:/Users/Moham/Documents/Music_player/login.txt");
    if(!file.open(QIODevice::WriteOnly| QIODevice::Text)){
        qDebug()<<"Could not open file";
        return;
    }
    QTextStream out(&file);
    for (int i=0;i<vc.size();i++) {
        if(i+1==usernum){
            out<<newpass<<endl;
        }
        else{out<<vc[i]<<endl;}
    }
    file.flush();
    file.close();
 vc.clear();
}
void find(){
    QFile file("C:/Users/Moham/Documents/Music_player/login.txt");
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
        qDebug()<<"Could not open file";
        return;
    }
    QTextStream out(&file);
    while(!out.atEnd()){
        QString line=out.readLine();
        vc.push_back(line);
    }
file.flush();
file.close();
file.resize(0);
final();
}
void get_num(){
    QFile file("C:/Users/Moham/Documents/Music_player/logged_in.txt");
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
        qDebug()<<"Could not open file";
        return;
    }
     QTextStream out(&file);
     bool ok;
    QString line=out.readLine();
    usernum=line.toInt(&ok,10);
     file.flush();
     file.close();
     find();
}
repass_continue::repass_continue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::repass_continue)
{
    ui->setupUi(this);
    repass_continue::setWindowTitle("MXA_Crusher_MUSIC_PLAYER :')");
    ui->lineEdit_2->setPlaceholderText("Enter password");
    ui->lineEdit_4->setPlaceholderText("Enter password");
}
repass_continue::~repass_continue()
{
    delete ui;
}

void repass_continue::on_checkBox_stateChanged(int arg1)
{
    ui->lineEdit_2->setEchoMode(ui->checkBox->checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password );

}
void repass_continue::on_checkBox_2_stateChanged(int arg1)
{
    ui->lineEdit_4->setEchoMode(ui->checkBox_2->checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password );

}

void repass_continue::on_pushButton_clicked()
{
    QString pass,passc;
    pass=ui->lineEdit_2->text();
    passc=ui->lineEdit_4->text();
    if(pass!=passc){
QMessageBox::critical(this,"Error","Password confirm is not correct");
            return ;
    }
if(pass.size()<8||pass.size()>16){QMessageBox::critical(this,"Watch out","Password must be 8 to 16");
        return;
    }
newpass=pass;
get_num();
this->close();
Dialog q;
q.setModal(true);
q.exec();
}

void repass_continue::on_pushButton_3_clicked()
{   this->close();
    repass q;
    q.setModal(true);
    q.exec();
}
