#include "gui/context_manager_widget/models/context_table_proxy_model.h"

#include "gui/gui_utils/sort.h"

#include <QDateTime>

namespace hal
{
    ContextTableProxyModel::ContextTableProxyModel(QObject* parent) : SearchProxyModel(parent)
    {

    }

    bool ContextTableProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
    {

        //TODO  somehow the program crashes with segfault if this method ever returns a false at the initial start

        QList<int> columns = mSearchOptions.getColumns();
        if(columns.empty()){
            //iterate over each column
            for(int index = 0; index < 2; index++){
                QString entry = sourceModel()->index(source_row, index, source_parent).data().toString();
                if(isMatching(mSearchString, entry))
                {
                    return true;
                }
            }
            return false;
        }else
        {
            for(int index : columns)
            {
                QString entry = sourceModel()->index(source_row, index, source_parent).data().toString();
                if(isMatching(mSearchString, entry))
                    return true;
            }
            return false;
        }

    }

    bool ContextTableProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
    {
        QVariant leftData = sourceModel()->data(left, Qt::UserRole);
        QVariant rightData = sourceModel()->data(right, Qt::UserRole);

        if(leftData.userType() == QMetaType::QDateTime)
            return leftData.toDateTime() > rightData.toDateTime();
        else
            return !(gui_utility::compare(gui_utility::mSortMechanism::natural, leftData.toString(), rightData.toString()));
    }

    void ContextTableProxyModel::startSearch(QString text, int options)
    {
        mSearchString = text;
        mSearchOptions = SearchOptions(options);
        invalidateFilter();
    }
}
