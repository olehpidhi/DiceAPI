#include "filtermodel.h"

FilterModel::FilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{

}

bool FilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
//    QString itemToFilter = sourceModel()->data(sourceModel()->index(source_row, 2)).toString().toLower();
//    if(itemToFilter.contains("california"))
//    {
        return true;
//    }

//    return false;
}
