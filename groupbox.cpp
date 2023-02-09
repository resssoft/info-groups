#include "groupbox.h"
#include <QDir>

GroupBox::GroupBox()
{
}

void GroupBox::init(QTreeWidget *w) {
    rootWIdget = w;
    qDebug() << QDir::currentPath() << QDir::currentPath() + QDir::separator() + "data";
    QDir dataDir = QDir(QDir::currentPath() + QDir::separator() + "data");

    if (!dataDir.exists()) {
        QDir().mkdir(QDir::currentPath() + QDir::separator() + "data");
    } else {
        qDebug() << "data dir exist";
    }
    w->setColumnCount(3);
    w->setHeaderLabels(QStringList{"Name", "Count", "Size"});
    scanDir(dataDir, NULL);

    return;
}

QTreeWidgetItem* GroupBox::add(QString name, QTreeWidgetItem *parent) {
    QTreeWidgetItem *item;
    if (parent == NULL) {
        item = new QTreeWidgetItem(rootWIdget);
        rootWIdget->addTopLevelItem(item);
    } else {
        item = new QTreeWidgetItem(parent);
    }
    item->setText(0, name);
    item->setText(1,"2");
    item->setText(2,"23B");
    return item;
}

QTreeWidgetItem* GroupBox::append(QString name, QTreeWidgetItem *parent) {
    QTreeWidgetItem *item;
    if (parent == NULL) {
        item = new QTreeWidgetItem(rootWIdget);
        rootWIdget->addTopLevelItem(item);
    } else {
        item = new QTreeWidgetItem(parent);
    }
    item->setText(0, name);
    item->setText(1,"0");
    item->setText(2,"0B");
    return item;
}

void GroupBox::update(GroupBoxItem item) {
    if (item.parent == NULL) {
        return;
    }
    item.parent->setText(0, item.name);
    item.parent->setText(1, item.count);
    item.parent->setText(2, item.size);
    return;
}

QString GroupBox::get(QTreeWidgetItem *item) {
    if (treeItems.contains(item)) {
        return treeItems[item].data;
    }
    return "";
}

void GroupBox::scanDir(QDir dir, QTreeWidgetItem *parent) {
    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QStringList dirList = dir.entryList();
    for (int i=0; i<dirList.size(); ++i)
    {
        QTreeWidgetItem *item = append(QString(dirList.at(i)), parent);
        QString newPath = QString("%1/%2").arg(dir.absolutePath()).arg(dirList.at(i));
        scanDir(QDir(newPath), item);
    }
    if (parent == NULL) {
        return;
    }
    dir.setNameFilters(QStringList("*.txt"));
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    qDebug() << "Scanning: " << dir.path();

    QStringList fileList = dir.entryList();
    for (int i=0; i<fileList.count(); i++)
    {
        QString name = fileList[i];
        name = name.replace(QRegularExpression(".txt$"), "");
        if (fileList[i] == "index.txt") {
            treeItems[parent] = fileData(dir.path() + QDir::separator() + "index.txt", "index.txt", parent);
            update(treeItems[parent]);
            continue;
        }
        QTreeWidgetItem *item = append(fileList[i], parent);
        treeItems[item] = fileData(dir.path() + QDir::separator() + fileList[i], fileList[i], item);
        update(treeItems[item]);
    }
}

GroupBoxItem GroupBox::fileData(QString path, QString name, QTreeWidgetItem *parent) {
    QFile f(path);
    if (!f.open(QFile::ReadOnly | QFile::Text)) return *GroupBoxItem().Item("","","","","",NULL);
    QTextStream in(&f);
    QString data = in.readAll();
    //qDebug() << path << f.size() << data;
    return *GroupBoxItem().Item(name, path, data, QString("%v").arg(f.size()), "", NULL);
}

