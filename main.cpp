#include "dialog.h"
#include <QApplication>
#include<QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
a.setWindowIcon(QIcon("C:/Users/Moham/Documents/Music_player/SAD.png"));
    Dialog w;
    w.show();
    return a.exec();
}
