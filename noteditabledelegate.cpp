#include "noteditabledelegate.h"

NotEditableDelegate::NotEditableDelegate(QObject *parent): QStyledItemDelegate(parent)
{

}

NotEditableDelegate::~NotEditableDelegate()
{

}

QWidget* NotEditableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return 0;
}
