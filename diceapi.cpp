#include "diceapi.h"

DiceAuthorizer::DiceAuthorizer(QObject* parent):
    QObject(parent),
    token(QString(""))
{
    connect(&mgr, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(setCredentials(QNetworkReply*,QAuthenticator*)));
}

void DiceAuthorizer::authorize(const QUrl &authUrl)
{    
    //creating request and setting
    //content type header
    QNetworkRequest request(authUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    //sending request and getting reply
    QNetworkReply* reply = mgr.get(request);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    processReply(reply);
}

//method invokes if server authorization is needed
//connected to
//QNetworkAccessManager.authenticationNeeded(QNetworkReply* reply, QAuthenticator* authenticator) signal
void DiceAuthorizer::setCredentials(QNetworkReply* reply, QAuthenticator* authenticator)
{
    Q_UNUSED(reply);
    authenticator->setUser(userName);
    authenticator->setPassword(password);
}

void DiceAuthorizer::processReply(QNetworkReply* reply)
{
    //check if reply is valid
    if(reply->error() == QNetworkReply::NoError)
    {
        //parsing JSON reply to get access_token
        QJsonDocument parsedReply = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
        QJsonObject jsonObj = parsedReply.object();
        token = jsonObj["access_token"].toString();
    }
    else
    {
        throw;
    }

}

QString DiceAuthorizer::getToken()
{
    return token;
}



DiceAPI::DiceAPI(QObject *parent):
    QObject(parent),
    token(QString()),
    JSONReply(QJsonObject())
{
    connect(&mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyRecieved(QNetworkReply*)));
}

DiceAPI::DiceAPI(QString pToken, QObject *parent):
    QObject(parent),
    token(pToken),
    JSONReply(QJsonObject())
{
    connect(&mgr, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(setCredentials(QNetworkReply*,QAuthenticator*)));
}

void DiceAPI::setCredentials(QNetworkReply* reply, QAuthenticator* auth)
{
    auth->setPassword(token);
    auth->setUser(APIUserName);
}

void DiceAPI::replyRecieved(QNetworkReply* reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QJsonDocument parsedReply = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
        JSONReply = parsedReply.object();
    }
    else
    {
        throw;
    }
}

QJsonObject DiceAPI::getData(const QString& query)
{    
    QUrlQuery qry(apiUrl);
    qry.addQueryItem("fields", "id, company, position");
    qry.addQueryItem("q",query);
    QUrl url(apiUrl);
    url.setQuery(qry);
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray((QString("bearer")+" "+token).toStdString().c_str()));

    QNetworkReply* reply = mgr.get(request);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //check if reply is valid
    if(reply->error() == QNetworkReply::NoError)
    {
        //parsing JSON reply to get access_token
        QJsonDocument parsedReply = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
        QJsonObject jsonObj = parsedReply.object();
        return jsonObj;
    }
    else
    {
        throw;
    }

}
