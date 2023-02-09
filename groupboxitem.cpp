#include "groupboxitem.h"
#include <QString>
#include <QTreeWidgetItem>

GroupBoxItem::GroupBoxItem()
{
}

GroupBoxItem* GroupBoxItem::Item(QString name, QString path, QString data, QString size, QString count, QTreeWidgetItem *parent)
{
    this->name = name;
    this->path = path;
    this->data = data;
    this->size = size;
    this->count = count;
    this->parent = parent;
    return this;
}
