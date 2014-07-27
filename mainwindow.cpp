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
    ui->tableView->setModel(proxyModel);
    getJobs();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::itemClicked(const QModelIndex &index)
{
    //QJsonObject jobInfo = api->getJobInfo(model->data(model->index(index.row(), 0), Qt::UserRole).toString());
    //ui->textBrowser->setText(jobInfo.value("description").toString());
}

void MainWindow::onJobInfoRecevied(const QJsonObject &jobInfo)
{
    model->setData(model->index(hash[jobInfo.value("id").toString()], 3), jobInfo.value("payRate").toString());
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

void MainWindow::getJobs()
{
    QJsonObject repl = api->getJobsList("android");
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
    proxyModel->setSourceModel(model);
}
