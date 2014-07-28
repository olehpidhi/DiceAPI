#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "diceapi.h"
#include "filtermodel.h"

#include <QStandardItemModel>
#include <QAbstractItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auth = new DiceAuthorizer();

    api = NULL;
    model = NULL;


    authorize();
    connectSignals();
    model = new QStandardItemModel(0, 4, this);
    proxyModel = new FilterModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);
    getJobs("android");
    getJobs("ios");
    getJobs("mobile");
    getJobs("windows phone");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::itemClicked(const QModelIndex &index)
{
    api->getJobInfo(model->data(model->index(index.row(), 0), Qt::UserRole).toString());
}

void MainWindow::onJobInfoRecevied(const QJsonObject &jobInfo)
{
    model->setData(model->index(hash[jobInfo.value("id").toString()], 3), jobInfo.value("payRate").toString());
    ui->textBrowser->setHtml(formatJson(jobInfo));
}

void MainWindow::connectSignals()
{
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)), Qt::UniqueConnection);
    connect(api, SIGNAL(jobInfoRecevied(QJsonObject)), this, SLOT(onJobInfoRecevied(QJsonObject)), Qt::UniqueConnection);
}

void MainWindow::authorize()
{
    if(auth)
    {
        auth->authorize(authUrl);
        api = new DiceAPI(auth->getToken());
    }
}

void MainWindow::getJobs(const QString &str)
{
    QJsonObject repl = api->getJobsList(str);
    QJsonArray jsonArray = repl.value("searchResults").toArray();
    const int size = jsonArray.count();
    const int rows = model->rowCount();
    model->insertRows(model->rowCount(), size);
    QString id;
    for(int i = 0; i < size; ++i)
    {
        model->setData(model->index(i + rows, 0), jsonArray.at(i).toObject().value("position").toObject().value("title").toString());
        model->setData(model->index(i + rows, 1), jsonArray.at(i).toObject().value("company").toObject().value("name").toString());
        model->setData(model->index(i + rows, 2), jsonArray.at(i).toObject().value("position").toObject().value("location").toObject().value("city").toString());
        id = jsonArray.at(i).toObject().value("id").toString();
        model->setData(model->index(i + rows, 0), id , Qt::UserRole);
        api->getJobInfo(id);
        hash.insert(id, i + rows);
    }
}

QString formatJson(const QJsonObject& toFormat)
{


    QJsonObject company = toFormat["company"].toObject();
    QJsonObject apply =  toFormat["apply"].toObject();
    QJsonObject position = toFormat["position"].toObject();
    QJsonObject location = position["location"].toObject();
    std::ostringstream htmlStream;
    htmlStream << "<p><strong>Company</strong></p>" <<
                  "<ul>" <<
                  "<li>Name:"<<company["name"].toString().toStdString()<<"<//li>"<<
                  "<li>Web Site"<<company["compURL"].toString().toStdString()<<"<//li>"<<
                  "<//ul>"<<
                  "<p><strong>Application<//strong><//p>"<<
                  "<ul>"<<
                  "<li>Application Method:"<<apply["applicationMethod"].toString().toStdString()<<"<//li>"<<
                  "<li>Email:"<<apply["email"].toString().toStdString()<<"<//li>"<<
                  "</ul>"<<
                  "<p>Creation Date</p>"<<
                  "<ul>"<<
                  "<li>"<<toFormat["creationDate"].toString().toStdString()<<"</li>"<<
                  "</ul>"<<
                  "<p>Description</p>"<<
                  "<ul>"<<
                  "<li>"<<toFormat["description"].toString().toStdString()<<"</li>"<<
                  "</ul>"<<
                  "<p><strong>Job Length</strong></p>"<<
                  "<ul>"<<
                  "<li>"<<toFormat["jobLength"].toString().toStdString()<<"</li>"
                  "</ul>"<<
                  "<p><strong>Pay Rate</strong></p>"<<
                  "<ul>"<<
                  "<li>"<<toFormat["payRate"].toString().toStdString()<<"</li></ul>"<<
                  "<p><strong>Position</strong></p>"<<
                  "<ul><li>Title:"<<position["title"].toString().toStdString()<<"</li><li>Location<ul>"<<
                  "<li>"<<location["city"].toString().toStdString()<<"</li>"
                  "<li>"<<location["country"].toString().toStdString()<<"</li>"
                  "<li>"<<location["postalCode"].toString().toStdString()<<"</li>"<<
                  "<li>"<<location["region"].toString().toStdString()<<"</li>"<<
                  "</ul></li></ul>"<<
                  "<p><strong>Status</strong></p>"<<
                  "<ul><li>"<<toFormat["status"].toString().toStdString()<<"</li>"<<
                  "</ul><p><strong>Skills</strong></p><ul>"<<
                  "<li>"<<toFormat["skills"].toString().toStdString()<<"</li></ul>"<<
                  "<p><strong>Tax Terms</strong></p><ul>"<<
                  "<li>"<<toFormat["taxTerms"].toString().toStdString()<<"</li>"<<
                  "</ul>"<<
                  "<p><strong>Telecommute option</strong></p><ul>"<<
                  "<li>"<<toFormat["telecommuteOption"].toString().toStdString()<<"</li></ul>"<<
                  "<p><strong>Link to Dice</strong>"<<toFormat["webURL"].toString().toStdString()<<"</p>";
    QString htmlData = QString::fromStdString(htmlStream.str());
    return htmlData;
}
