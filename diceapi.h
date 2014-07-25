#ifndef DICEAPI_H
#define DICEAPI_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

const QUrl authUrl = QUrl("https://secure.dice.com/oauth/token?grant_type=client_credentials");
const QUrl apiUrl = QUrl("https://api.dice.com/jobs");

const QString userName = "diceHackathon";
const QString password = "9fc52528-080d-4f0c-becd-45acf46bac4e";

class DiceAuthorizer : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager mgr;
    QString token;
public:
    explicit DiceAuthorizer(QObject* parent = 0);
    void authorize(const QUrl &authUrl);
    QString getToken();
public slots:
    void setCredentials(QNetworkReply*reply, QAuthenticator*authenticator);
    void processReply(QNetworkReply*);
};


class DiceAPI : public QObject
{
    Q_OBJECT
private:
    QString token;
    QJsonObject JSONReply;
    QNetworkAccessManager mgr;
public:
    explicit DiceAPI(QObject *parent = 0);
   QJsonObject getData(const QString& query);

signals:

public slots:
    void replyRecieved(QNetworkReply*);

};

#endif // DICEAPI_H
