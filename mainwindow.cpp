#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QMap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->newGroupName->hide();
    ui->isNewGroupTop->hide();
    ui->searchGroupText->hide();
    ui->searchDataInput->hide();

    QAction *closeApp = new QAction(this);
    closeApp->setShortcut(Qt::Key_Q | Qt::SHIFT | Qt::CTRL);
    connect(closeApp, SIGNAL(triggered()), this, SLOT(close()));
    this->addAction(closeApp);

    QAction *searchAction = new QAction(this);
    searchAction->setShortcut(Qt::Key_F | Qt::CTRL);
    connect(searchAction, SIGNAL(triggered()), this, SLOT(searchAction()));
    this->addAction(searchAction);

    groupBox.init(ui->groupsTree);
    statusBarUpdate();
}

void MainWindow::searchAction()
{
    if (ui->plainTextEdit->hasFocus()) {
        qDebug() << "plainTextEdit ";
        ui->searchDataInput->show();
        ui->dateTimeEdit->hide();
        ui->pushButton->hide();
    }
    if (ui->dateTimeEdit->hasFocus()) {
        qDebug() << "dateTimeEdit ";
    }
    if (ui->groupsTree->hasFocus()) {
        qDebug() << "groupsTree ";
        ui->searchGroupText->show();
    }
    qDebug() << "searchAction ";
}

void MainWindow::statusBarUpdate()
{
    qDebug() << "statusBarUpdate ";
    QString statusBarText = "Choice group";
    if (ui->groupsTree->currentItem() != NULL) {
        statusBarText = tr("Group: ") + ui->groupsTree->currentItem()->text(0);
    }
    ui->statusbar->showMessage(statusBarText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString clipboardText = clipboard->text();
    ui->plainTextEdit->appendPlainText(clipboardText);
}

void MainWindow::on_groupsTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    ui->groupsTree->editItem(item, column);
        //item->setFlags(tmp | Qt::ItemIsEditable);
        //item->setFlags(tmp ^ Qt::ItemIsEditable);

}

void MainWindow::on_newGroupName_editingFinished()
{
}

void MainWindow::on_newGroupName_inputRejected()
{
}


void MainWindow::on_addGroupButtom_clicked()
{
    ui->newGroupName->show();
    ui->isNewGroupTop->show();
    ui->addGroupButtom->hide();
    ui->delGroupButtom->hide();
}

void MainWindow::on_delGroupButtom_clicked()
{
    qDebug() << "TODO on_delGroupButtom_clicked";
}

void MainWindow::on_newGroupName_returnPressed()
{
    QTreeWidgetItem *item;
    if (ui->isNewGroupTop->isChecked() || ui->groupsTree->currentItem() == NULL) {
        item = new QTreeWidgetItem(ui->groupsTree);
    } else {
        item = new QTreeWidgetItem(ui->groupsTree->currentItem());
        ui->groupsTree->currentItem()->setExpanded(true);
    }
    groupBox.add(ui->newGroupName->text(), item);
    item->setText(0,ui->newGroupName->text());
    item->setText(1,"0");
    item->setText(2,"0B");

    ui->newGroupName->hide();
    ui->isNewGroupTop->hide();
    ui->addGroupButtom->show();
    ui->delGroupButtom->show();
}

void MainWindow::on_groupsTree_itemClicked(QTreeWidgetItem *item, int column)
{
    QString data = groupBox.get(item);
    ui->plainTextEdit->setPlainText(data);
    statusBarUpdate();
    //TODO: load group data
}

void MainWindow::on_searchGroupText_returnPressed()
{
    qDebug() << "TODO search group";
    ui->searchGroupText->hide();
}

void MainWindow::on_searchDataInput_returnPressed()
{
    qDebug() << "TODO on_searchDataInput_returnPressed";
    ui->searchDataInput->hide();
    ui->dateTimeEdit->show();
    ui->pushButton->show();
}


void MainWindow::on_plainTextEdit_textChanged()
{
    //qDebug() << "on_plainTextEdit_textChanged";
}


void MainWindow::on_searchDataInput_editingFinished()
{
    ui->searchDataInput->hide();
    ui->dateTimeEdit->show();
    ui->pushButton->show();
}


void MainWindow::on_searchGroupText_editingFinished()
{
    ui->searchGroupText->hide();
}


void MainWindow::on_plainTextEdit_modificationChanged(bool arg1)
{
    qDebug() << "on_plainTextEdit_modificationChanged";
}

