#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include "sparse.h"
#include "ui_sparse.h"

sparse::sparse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sparse)
{
    ui->setupUi(this);

    int ret = 0;

    //Open sql db
    m_DB = QSqlDatabase::addDatabase(tr("QSQLITE"));
    m_DB.setHostName(tr("sparse.db"));
    m_DB.setDatabaseName(tr("sparse.db"));

    ret = m_DB.open();
    if (true != ret)
    {
        qDebug() << "Sql open failed!";
        return;
    }

    //Select Sql db
    m_pTableModel = new QSqlTableModel;
    m_pTableModel->setSort(0, Qt::AscendingOrder);
    m_pTableModel->setTable(tr("sparse"));
    m_pTableModel->select();

    //Show table
    ui->tableView->setModel(m_pTableModel);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


}

sparse::~sparse()
{
    delete ui;
}

void sparse::on_pushButtonFind_clicked()
{
    m_pTableModel->setTable(tr("sparse"));
    m_pTableModel->setFilter(tr("cmdcode = '%1'").arg("1e3d"));

    ui->tableView->setModel(m_pTableModel);
}
