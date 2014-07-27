#include <QCoreApplication>
#include "diceapi.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DiceAuthorizer auth;
    auth.authorize(authUrl);

    DiceAPI api(auth.getToken());
    QJsonObject repl = api.getData("ios");
    qDebug() << repl;
    return a.exec();
}

