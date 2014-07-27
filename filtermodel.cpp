#include "filtermodel.h"

FilterModel::FilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{

}

bool FilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if(sourceModel()->data(sourceModel()->index(source_row, 3)).toString() == "open")
        return true;
    return false;
}
