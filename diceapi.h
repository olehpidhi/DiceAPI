#ifndef DICEAPI_H
#define DICEAPI_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class DiceAPI : public QObject
{
    Q_OBJECT
private:
    static QUrl authUrl;
    static QUrl apiUrl;
    QString userName;
    QString password;
    QString token;
    QNetworkAccessManager mgr;
public:
    explicit DiceAPI(QObject *parent = 0);
    void authorize();
    QJsonObject getData(const QString& query);

signals:

public slots:
    void setCredentials(QNetworkReply*reply, QAuthenticator*authenticator);

};

#endif // DICEAPI_H
