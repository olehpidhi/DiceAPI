#include <QCoreApplication>
#include "diceapi.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DiceAuthorizer auth;
    auth.authorize(authUrl);

    return a.exec();
}

