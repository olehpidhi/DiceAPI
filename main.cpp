#include <QCoreApplication>
#include "diceapi.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DiceAuthorizer auth;
    auth.authorize(authUrl);
    qDebug() << auth.getToken();
    return a.exec();
}

