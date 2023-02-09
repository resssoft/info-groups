#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <groupbox.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void statusBarUpdate();

private slots:
    void searchAction();

    void on_pushButton_clicked();

    void on_groupsTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_newGroupName_editingFinished();

    void on_newGroupName_inputRejected();

    void on_addGroupButtom_clicked();

    void on_delGroupButtom_clicked();

    void on_newGroupName_returnPressed();

    void on_groupsTree_itemClicked(QTreeWidgetItem *item, int column);

    void on_searchGroupText_returnPressed();

    void on_searchDataInput_returnPressed();

    void on_plainTextEdit_textChanged();

    void on_searchDataInput_editingFinished();

    void on_searchGroupText_editingFinished();

    void on_plainTextEdit_modificationChanged(bool arg1);

private:
    Ui::MainWindow *ui;
    GroupBox groupBox;
};
#endif // MAINWINDOW_H
