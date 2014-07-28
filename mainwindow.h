#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <string>
#include <sstream>
class DiceAuthorizer;
class DiceAPI;
class QAbstractItemModel;
class FilterModel;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void itemClicked(const QModelIndex &index);
    void onJobInfoRecevied(const QJsonObject &jobInfo);

private:
    void connectSignals();
    void authorize();
    void getJobs(const QString &str);

private:
    Ui::MainWindow *ui;
    DiceAuthorizer *auth;
    DiceAPI *api;
    QAbstractItemModel *model;
    FilterModel *proxyModel;
    QHash<QString, int> hash;

};

QString formatJson(const QJsonObject&);

#endif // MAINWINDOW_H
