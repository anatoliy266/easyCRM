#ifndef NOTEDITABLEDELEGATE_H
#define NOTEDITABLEDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QStyledItemDelegate>

class NotEditableDelegate : public QStyledItemDelegate
{
public:
    NotEditableDelegate(QObject* parent);
    ~NotEditableDelegate();
protected:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const ;
};

#endif // NOTEDITABLEDELEGATE_H
