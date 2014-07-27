#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QSortFilterProxyModel>

class FilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FilterModel(QObject *parent = 0);

signals:

public slots:

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

};

#endif // FILTERMODEL_H
