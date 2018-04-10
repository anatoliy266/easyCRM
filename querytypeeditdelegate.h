#ifndef QUERYTYPEEDITDELEGATE_H
#define QUERYTYPEEDITDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QItemDelegate>
#include <string>
#include <vector>

class queryTypeEditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit queryTypeEditDelegate(QObject *parent = nullptr);
    ~queryTypeEditDelegate();
public slots:
    void getQTypes(QStringList qTypes);
protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    private:
      QStringList Items;

};

#endif // QUERYTYPEEDITDELEGATE_H
