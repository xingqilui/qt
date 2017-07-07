#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QAbstractItemView>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Connect sql
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("feature.db");

    if (!db.open())
    {
        QMessageBox::information(this, "Info", "Open sql failed!");
        return;
    }

    //show feature db
    QSqlTableModel *pModelFeature = new QSqlTableModel;
    pModelFeature->setTable("feature");
    pModelFeature->setSort(0, Qt::AscendingOrder);
    pModelFeature->select();

    ui->tableView->setModel(pModelFeature);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    //show story db
    QSqlTableModel *pModelStory = new QSqlTableModel;
    pModelStory->setTable("story");
    pModelStory->setSort(0, Qt::AscendingOrder);
    pModelStory->select();

    ui->tableView_story->setModel(pModelStory);
    ui->tableView_story->resizeColumnsToContents();
    ui->tableView_story->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_story->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_story->setSelectionBehavior(QAbstractItemView::SelectRows);


    QStringList tables = db.tables();
    QStringListIterator itr(tables);
    QString tableName;

    while (itr.hasNext())
    {
        tableName += itr.next() + "\n";
    }

    ui->textEdit->setText(tableName);

    db.close();
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
}


