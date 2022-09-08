#include "help.h"
#include "ui_help.h"
#include<QSize>
#include<QHeaderView>
#include<QListWidget>
#include<QMessageBox>
#include<QVector>
#include<QPair>
#include<QtAlgorithms>
#include<QBrush>
#include<QFile>
#include<QString>
const int song_length=37;
static song songdata[100];
 int c1a_Se=0,m1akan=0,usernumber1,cnt=0,cnt1=0;
QMultiMap<double,song>oneforall;
song* viewer;
QMultiMap<double,song>::iterator itr;
QVector<QPair<double,int>>rate_vc;
QVector<int>filler;
static QSize myGetQTableWidgetSize(QTableWidget *t) {
   int w = t->verticalHeader()->width() + 4;
   for (int i = 0; i < t->columnCount(); i++)
      w += t->columnWidth(i);
   int h = t->horizontalHeader()->height() + 4;
   for (int i = 0; i < t->rowCount(); i++)
      h += t->rowHeight(i);
   return QSize(777,500);
}
static void myRedoGeometry(QWidget *w) {
   const bool vis = w->isVisible();
   const QPoint pos = w->pos();
   w->hide();
   w->show();
   w->setVisible(vis);
   if (vis && !pos.isNull())
      w->move(pos);
}
void build_struct(){
QFile file("C:/Users/Moham/Documents/Music_player/songdata.txt");
if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    qDebug()<<"Could not open file";
    return;
}
QTextStream in(&file);
QString data;
while (!in.atEnd()) { data=in.readLine();   c1a_Se++;
    if(c1a_Se==1){songdata[m1akan].songnameshow=data;}
    if(c1a_Se==2){songdata[m1akan].singer=data;}
    if(c1a_Se==3){songdata[m1akan].album=data;}
    if(c1a_Se==4){  songdata[m1akan].release_year=data;}
    if(c1a_Se==5){songdata[m1akan].songpath=data;}
    if(c1a_Se==6){songdata[m1akan].type=data; c1a_Se=0, m1akan++;}
}
file.flush();
file.close();
}
void build_oneforall(){
  QString line,word1,word2;
  usernumber1=(usernumber1-1)*song_length;
      double rate; int position,q=0;
      QFile file("C:/Users/Moham/Documents/Music_player/rate.txt");
      if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
          qDebug()<<"Could not open file";
          return;
      }
      QTextStream in(&file);
      while(!in.atEnd()){
      line=in.readLine();
      word1=line.mid(0,3);
      word2=line.mid(3,8);
      bool ok;
      rate=word1.toDouble(&ok);
      position=word2.toInt(&ok,10);
      q++;
       if(q==(usernumber1+song_length+1))
       { file.flush();
         file.close();
           return ;
       }
       if(rate>=2.0&&q>usernumber1)
       {
           oneforall.insert(rate,songdata[position]);
       }
       }
file.flush();
file.close();
}
void logged_in(void){
  QString username,password,line; int cnt=0;
  QFile file("C:/Users/Moham/Documents/Music_player/logged_in.txt");
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
      qDebug()<<"Could not open file";
      return;
  }
   QTextStream in(&file);
   while (!in.atEnd()) {
       cnt++;
       line = in.readLine();
       if(cnt==1){username=line;}
       if(cnt==2){password=line;}
       if(cnt==3){bool ok; usernumber1=line.toInt(&ok,10);}
       }
}
QString string_trick(QString s){
    s=s.toLower();
    s=s.simplified();
    s.replace( " ", "" );
    return  s;
}
song* search(QString tpxt,QString choice ){
    song* arr=new song[1000];
    tpxt=string_trick(tpxt);
    int i=0;
for(itr=oneforall.begin();itr!=oneforall.end();itr++){
  QString s;
     if(choice=="Title"){
         s=itr.value().songnameshow;
          s=string_trick(s);
         if(s.contains(tpxt)) {
             arr[i]=itr.value();
             i++,cnt++;
         }
     }
     if(choice=="Artist"){
         s=itr.value().singer;
         s=string_trick(s);
         if(s.contains(tpxt)){
             arr[i]=itr.value();
             i++,cnt++;
         }
     }
     if(choice=="Genere"){
        s=itr.value().type;
        s=string_trick(s);
        if(s.contains(tpxt)){
            arr[i]=itr.value();
            i++,cnt++;
        }
     }
     if(choice=="Release year"){
         s=itr.value().release_year;
         s=string_trick(s);
         if(s.contains(tpxt)){
             arr[i]=itr.value();
             i++,cnt++;
         }
     }
     if(choice=="Album"){
         s=itr.value().album;
           s=string_trick(s);
         if(s.contains(tpxt)){
             arr[i]=itr.value();
             i++,cnt++;
         }
     }
}
return arr;
}
void continue_editing(int row_number,double ret){
    int counter =0,ans=0; QString ans1;
    for(itr=oneforall.begin();itr!=oneforall.end();itr++){
     counter++;
     if(counter==row_number){
         ans1=itr.value().songnameshow;
         break;
     }
    }
  oneforall.clear();
    for(int i=0;i<song_length;i++){
        if(songdata[i].songnameshow==ans1){ans=i;  break;}
    }
    QFile file("C:/Users/Moham/Documents/Music_player/rate.txt");
    if(!file.open(QIODevice::WriteOnly| QIODevice::Text)){
        qDebug()<<"Could not open file";
        return;
    }
   qDebug()<<usernumber1<<endl;
    QTextStream in(&file);
    for(int i=0;i<rate_vc.size();i++){
        if(i>=usernumber1&&(i<(usernumber1+song_length))){
            if(rate_vc[i].second==ans){
                if(ret>=2.0){oneforall.insert(ret,songdata[rate_vc[i].second]);}
                in<<ret<<"  "<<rate_vc[i].second<<endl;
            }
            else {in<<rate_vc[i].first<<"  "<<rate_vc[i].second<<endl;
                if(rate_vc[i].first>=2.0)
            oneforall.insert(rate_vc[i].first,songdata[rate_vc[i].second]);
            }
        }
        else{ in<<rate_vc[i].first<<"  "<<rate_vc[i].second<<endl;
        }
    }
    file.flush();
    file.close();
}
void edit_rate(int row_number,double ret){
    row_number++;
    rate_vc.clear();
    double rate; int position; QString line,word1,word2;
    QFile file("C:/Users/Moham/Documents/Music_player/rate.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Could not open file";
        return;
    }
    QTextStream in(&file);
    while(!in.atEnd()){
    line=in.readLine();
    word1=line.mid(0,3);
    word2=line.mid(3,8);
    bool ok;
    rate=word1.toDouble(&ok);
    position=word2.toInt(&ok,10);
    rate_vc.push_back({rate,position});
     }
    file.flush();
    file.close();
    continue_editing(row_number,ret);
}
void random_vector_generator(){
    filler.clear();
    for(int i=0;i<oneforall.size();i++){filler.push_back(i);}
    srand(time(NULL));
    for(int i=filler.size()-1;i>0;i--){
        int j= rand()%(i+1);
        int temp=filler[j];
        filler.replace(j,filler[i]);
         filler.replace(i,temp);
    }
}
void random_vector_generator(int size){
    filler.clear();
    for (int i=0;i<size;i++) {
        filler.push_back(i);
        srand(time(NULL));
        for(int i=filler.size()-1;i>0;i--){
            int j= rand()%(i+1);
            int temp=filler[j];
            filler.replace(j,filler[i]);
             filler.replace(i,temp);
        }
    }
}
HELP::HELP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HELP)
{
    ui->setupUi(this);
    build_struct();
    logged_in();
    build_oneforall();
  HELP::setFixedSize(QSize(1200,700));
  QVBoxLayout *vbox = new QVBoxLayout;
  playlist = new QMediaPlaylist;
  player = new QMediaPlayer(this);
  ext=new QMediaPlaylist;
  player->setPlaylist(ext);
connect(player, &QMediaPlayer::positionChanged, this, &HELP::on_positionChanged);
connect(player, &QMediaPlayer::durationChanged, this, &HELP::on_durationChanged);
  tablel= new QTableWidget(this);
  tablel->setRowCount(oneforall.size());
  tablel->setColumnCount(6);
    int cnt=0;
    list=new QListWidget;
    for(itr=oneforall.begin();itr!=oneforall.end();itr++){
        ext->addMedia(QUrl("C:/Users/Moham/Documents/Music_player/"+itr.value().songpath));
        ui->listWidget->addItem(itr.value().songnameshow);
        item=new QTableWidgetItem;
        item2=new QTableWidgetItem;
        item3=new QTableWidgetItem;
        item4=new QTableWidgetItem;
        item5=new QTableWidgetItem;
        item6=new QTableWidgetItem;
        item->setText(itr.value().songnameshow);
        tablel->setItem(cnt,0,item);
         tablel->item(cnt,0)->setTextColor(Qt::white);
        item2->setText(itr.value().singer);
        tablel->setItem(cnt,1,item2);
         tablel->item(cnt,1)->setTextColor(Qt::white);
        item3->setText(itr.value().type);
        tablel->setItem(cnt,2,item3);
         tablel->item(cnt,2)->setTextColor(Qt::white);
        item4->setText(itr.value().release_year);
        tablel->setItem(cnt,3,item4);
         tablel->item(cnt,3)->setTextColor(Qt::white);
        item5->setText(itr.value().album);
         tablel->setItem(cnt,4,item5);
          tablel->item(cnt,4)->setTextColor(Qt::white);
         double r=itr.key();
         QString valueAsString = QString::number(r);
          item6->setText(valueAsString);
         tablel->setItem(cnt,5,item6);
            tablel->item(cnt,5)->setTextColor(Qt::white);
        cnt++;
    }
    tablel->setAlternatingRowColors(true);
     tablel->setStyleSheet("alternate-background-color:#000000;background-color:#1A1A1A;");
     ui->listWidget->setAlternatingRowColors(true);
     ui->listWidget->setStyleSheet("alternate-background-color:#e6e6e6;background-color:#FFFFFF;");
      vh=new QHeaderView(Qt::Vertical);
         vh->hide();
   tablel->setVerticalHeader(vh);
  vbox->addWidget(tablel);
 layout()->setSizeConstraint(QLayout::SetMinimumSize);
 tablel->setVerticalHeaderItem(1, new QTableWidgetItem("two"));
 myRedoGeometry(this);
 tablel->setMaximumSize(myGetQTableWidgetSize(tablel));
 tablel->setMinimumSize(tablel->maximumSize());
 tablel->setHorizontalHeaderLabels(QString("Title;Artist;Genere;Release year;Album;Rate;").split(";"));
 ui->lineEdit->setPlaceholderText("Search");
 ui->lineEdit_2->setPlaceholderText("Enter rate");
}
HELP::~HELP()
{
    delete ui;
}
void HELP::on_sliderProgress_sliderMoved(int position)
{
    player->setPosition(position);
}
void HELP::on_sliderVolume_sliderMoved(int position)
{
    player->setVolume(position);
}
void HELP::on_pushButton_clicked()
{
HELP::player->play();
}
void HELP::on_pushButton_2_clicked()
{
    HELP::player->pause();
}
void HELP::on_pushButton_3_clicked()
{
    HELP::ext->next();
}
void HELP::on_pushButton_4_clicked()
{
    HELP::ext->previous();
}
void HELP::on_pushButton_5_clicked()
{ //shuffle
ext->clear(); ui->listWidget->clear();
    if(ui->lineEdit->text()==""){
            random_vector_generator();
   for(int i=0;i<filler.size();i++){
      int cnit=0;
        for(itr =oneforall.begin();itr!=oneforall.end();itr++){
            if(cnit==filler[i]){
       ext->addMedia(QUrl("C:/Users/Moham/Documents/Music_player/"+itr.value().songpath));
                ui->listWidget->addItem(itr.value().songnameshow);
            }   cnit++;}
     }
    }
    else{
        random_vector_generator(cnt1);
        for(int i=0;i<filler.size();i++){
            for(int j=0;j<cnt1;j++){
         if (j==filler[i]){   ext->addMedia(QUrl("C:/Users/Moham/Documents/Music_player/"+viewer[j].songpath));
         ui->listWidget->addItem(viewer[j].songnameshow);
         }
              }
    }
}
}
void HELP::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
}
void HELP::on_durationChanged(qint64 position)
{
    ui->sliderProgress->setMaximum(position);
}

void HELP::on_lineEdit_textChanged(const QString &arg1)
{   ui->listWidget->clear();
    ext->clear();    
    QString search1=ui->lineEdit->text(),choice=ui->comboBox->currentText();
    if(search1!=""){
       viewer=search(search1,choice);}
    else{
        int cnt=0;
        list=new QListWidget;
        for(itr=oneforall.begin();itr!=oneforall.end();itr++){
            ext->addMedia(QUrl("C:/Users/Moham/Documents/Music_player/"+itr.value().songpath));
            ui->listWidget->addItem(itr.value().songnameshow);
            item=new QTableWidgetItem;
            item2=new QTableWidgetItem;
            item3=new QTableWidgetItem;
            item4=new QTableWidgetItem;
            item5=new QTableWidgetItem;
            item6=new QTableWidgetItem;
            item->setText(itr.value().songnameshow);
            tablel->setItem(cnt,0,item);
             tablel->item(cnt,0)->setTextColor(Qt::white);
            item2->setText(itr.value().singer);
            tablel->setItem(cnt,1,item2);
             tablel->item(cnt,1)->setTextColor(Qt::white);
            item3->setText(itr.value().type);
            tablel->setItem(cnt,2,item3);
             tablel->item(cnt,2)->setTextColor(Qt::white);
            item4->setText(itr.value().release_year);
            tablel->setItem(cnt,3,item4);
             tablel->item(cnt,3)->setTextColor(Qt::white);
            item5->setText(itr.value().album);
             tablel->setItem(cnt,4,item5);
              tablel->item(cnt,4)->setTextColor(Qt::white);
              double r=itr.key();
              QString valueAsString = QString::number(r);
               item6->setText(valueAsString);
              tablel->setItem(cnt,5,item6);
                 tablel->item(cnt,5)->setTextColor(Qt::white);
            cnt++;
        }
        return;}
    if(cnt==0&&ui->listWidget->count()==0){QMessageBox::critical(this,"404","Not founded"); return;}
   ext=new QMediaPlaylist;
   player=new QMediaPlayer(this);
   player->setPlaylist(ext);
   for(int i=0;i<cnt;i++){
    ext->addMedia(QUrl("C:/Users/Moham/Documents/Music_player/"+viewer[i].songpath));
    ui->listWidget->addItem(viewer[i].songnameshow);
   }
 cnt1=cnt;cnt=0;
 connect(player, &QMediaPlayer::positionChanged, this, &HELP::on_positionChanged);
  connect(player, &QMediaPlayer::durationChanged, this, &HELP::on_durationChanged);
delete [] viewer;
}
void HELP::on_pushButton_6_clicked()
{  connect(player, &QMediaPlayer::positionChanged, this, &HELP::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &HELP::on_durationChanged);
    QString s=ui->lineEdit_2->text();
    bool ok;
    double x=s.toDouble(&ok);
    if(x>5||x<1){QMessageBox::warning(this,"Erorr","The range is from 1 to 5");}
    else{
    edit_rate(tablel->currentRow(),x);
    tablel->setRowCount(oneforall.size());
    cnt=0;
    ui->listWidget->clear();
    ext->clear();
    for(itr=oneforall.begin();itr!=oneforall.end();itr++){
        ext->addMedia(QUrl("C:/Users/Moham/Documents/Music_player/"+itr.value().songpath));
        item=new QTableWidgetItem;
        item2=new QTableWidgetItem;
        item3=new QTableWidgetItem;
        item4=new QTableWidgetItem;
        item5=new QTableWidgetItem;
        item6=new QTableWidgetItem;
        item->setText(itr.value().songnameshow);
        tablel->setItem(cnt,0,item);
         tablel->item(cnt,0)->setTextColor(Qt::white);
        item2->setText(itr.value().singer);
        tablel->setItem(cnt,1,item2);
         tablel->item(cnt,1)->setTextColor(Qt::white);
        item3->setText(itr.value().type);
        tablel->setItem(cnt,2,item3);
         tablel->item(cnt,2)->setTextColor(Qt::white);
        item4->setText(itr.value().release_year);
        tablel->setItem(cnt,3,item4);
         tablel->item(cnt,3)->setTextColor(Qt::white);
        item5->setText(itr.value().album);
         tablel->setItem(cnt,4,item5);
          tablel->item(cnt,4)->setTextColor(Qt::white);
          double r=itr.key();
          QString valueAsString = QString::number(r);
           item6->setText(valueAsString);
          tablel->setItem(cnt,5,item6);
             tablel->item(cnt,5)->setTextColor(Qt::white);
        cnt++;
     ui->listWidget->addItem(itr.value().songnameshow);
    }
    player->setPlaylist(ext);
    }
}
void HELP::on_pushButton_7_clicked()
{   HELP::player->stop();
    this->close();
    oneforall.clear();
    tablel->clear();
    Dialog q;
    q.setModal(true);
    q.exec();
}
