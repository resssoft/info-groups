#ifndef GROUPBOX_H
#define GROUPBOX_H
#include <QStringList>
#include <QString>
#include <QTreeWidgetItem>
#include <QList>
#include <groupboxitem.h>
#include <QTreeWidget>
#include <QDir>

class GroupBox
{
public:
    GroupBox();

    QTreeWidgetItem* add(QString name, QTreeWidgetItem *parent);
    QTreeWidgetItem* append(QString name, QTreeWidgetItem *parent);
    void update(GroupBoxItem item);
    QList<QTreeWidgetItem> items();
    void init(QTreeWidget *w);
    void scanDir(QDir dir, QTreeWidgetItem *parent);
    QString get(QTreeWidgetItem *item);

    GroupBoxItem fileData(QString path, QString name, QTreeWidgetItem *parent);

    QTreeWidget *rootWIdget;

private:
    QList<GroupBoxItem> treeData;
    QMap<QTreeWidgetItem*,GroupBoxItem> treeItems;
};

#endif // GROUPBOX_H
