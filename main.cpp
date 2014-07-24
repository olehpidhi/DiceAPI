#include <QCoreApplication>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>


int main(int argc, char *argv[])
{

}

QString userName = "diceHackathon";
QString password = "9fc52528-080d-4f0c-becd-45acf46bac4e";

void sendRequest()
{
    QNetworkAccessManager* mgr = new QNetworkAccessManager();
    QUrl url("https://secure.dice.com/oauth/token?grant_type=client_credentials");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QString credentials = userName + ":" + password;
    QByteArray ba;
    ba.append(credentials);

    request.setRawHeader(QByteArray("Authorization"), ba.toBase64());

    QNetworkReply* reply = mgr->get(request);
    qDebug() << reply->readAll();

}

