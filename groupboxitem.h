#ifndef GROUPBOXITEM_H
#define GROUPBOXITEM_H
#include <QString>
#include <QTreeWidgetItem>


class GroupBoxItem
{
public:
    GroupBoxItem();
    GroupBoxItem* Item(QString name, QString path, QString data, QString size, QString count, QTreeWidgetItem *parent);
    QString name;
    QString data;
    QString path;
    QString size;
    QString count;
    QTreeWidgetItem *parent;
};

#endif // GROUPBOXITEM_H
