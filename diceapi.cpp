#include "diceapi.h"

DiceAPI::DiceAPI(QObject *parent) :
    QObject(parent),
    authUrl("https://secure.dice.com/oauth/token?grant_type=client_credentials"),
    apiUrl("https://api.dice.com/jobs"),
    userName(QString()),
    password(QString()),
    token(QString())
{
    connect(&mgr, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(setCredentials(QNetworkReply*,QAuthenticator*)));

}

void DiceAPI::authorize()
{
    //creating request and setting
    //content type header
    QNetworkRequest request(authUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    //sending request and getting reply
    QNetworkReply reply = mgr.get(request);

    //check if reply is valid
    if(reply.error() == QNetworkReply::NoError)
    {
        //parsing JSON reply to get access_token
        QJsonDocument parsedReply = QJsonDocument::fromJson(QString(reply.readAll()).toUtf8());
        QJsonObject jsonObj = parsedReply.object();
        token = jsonObj["access_token"].toString();
    }
    else
    {
        throw;
    }

}

//method invokes if server authorization is needed
//connected to
//QNetworkAccessManager.authenticationNeeded(QNetworkReply* reply, QAuthenticator* authenticator) signal
void DiceAPI::setCredentials(QNetworkReply* reply, QAuthenticator* authenticator)
{
    if(reply->url() == authUrl)
    {
        authenticator->setUser(userName);
        authenticator->setPassword(password);
    }
    else
    {
        authenticator->setUser("bearer");
        authenticator->setPassword(token);
    }
}

QJsonObject DiceAPI::getData(const QString& query)
{
    QNetworkRequest request(apiUrl);
    QUrlQuery qry(apiUrl);
    qry.addQueryItem("fields", "id, company, position");
    qry.addQueryItem(query);

    QNetworkReply reply = mgr.get(request);

    //check if reply is valid
    if(reply.error() == QNetworkReply::NoError)
    {
        //parsing JSON reply to get access_token
        QJsonDocument parsedReply = QJsonDocument::fromJson(QString(reply.readAll()).toUtf8());
        QJsonObject jsonObj = parsedReply.object();
        return jsonObj;
    }
    else
    {
        throw;
    }

}
