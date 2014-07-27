#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    /*
    QCoreApplication a(argc, argv);
    DiceAuthorizer auth;
    auth.authorize(authUrl);

    DiceAPI api(auth.getToken());
    QJsonObject repl = api.getJobsList("ios");
    //qDebug() << repl;
    QJsonObject jobInfo = api.getJobInfo("201aa3136587319466e985b513e159bf");
    qDebug() << jobInfo;*/

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

