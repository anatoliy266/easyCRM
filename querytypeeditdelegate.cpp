#include "querytypeeditdelegate.h"
#include <QComboBox>
#include <QWidget>
#include <QModelIndex>
#include <QApplication>
#include <QString>
#include <QItemDelegate>

#include <iostream>


#include <QComboBox>
#include <QWidget>
#include <QModelIndex>
#include <QApplication>
#include <QString>

#include <iostream>

queryTypeEditDelegate::queryTypeEditDelegate(QObject *parent)
:QItemDelegate(parent)
{
  Items.clear();
}

queryTypeEditDelegate::~queryTypeEditDelegate()
{

}


QWidget *queryTypeEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
  QComboBox* editor = new QComboBox(parent);
  for(int i = 0; i < Items.count(); i++)
    {
    editor->addItem(Items.value(i));
    }
  return editor;
}

void queryTypeEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  QString value = index.model()->data(index, Qt::EditRole).toString();
  comboBox->setCurrentText(value);
}

void queryTypeEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void queryTypeEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}

void queryTypeEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyleOptionViewItemV4 myOption = option;
  QString text = index.model()->data(index, Qt::DisplayRole).toString();

  myOption.text = text;

  QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
}

void queryTypeEditDelegate::getQTypes(QStringList qTypes)
{
    for (int i = 0; i<qTypes.count(); i++)
    {
        Items.append(qTypes.value(i));
    }
}
