#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include "sparse.h"
#include "ui_sparse.h"


enum
{
    CMDCODE,
    CMDNAME,
    OUTERHEADLIST,
    INNERHEADLIST,
    INNERBODYLIST
};

sparse::sparse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sparse)
{
    ui->setupUi(this);

    int ret = 0;

    //Open sql db
    m_DB = QSqlDatabase::addDatabase(tr("QSQLITE"));
    m_DB.setDatabaseName(tr("sparse.db"));
    m_DB.setHostName(tr("127.0.0.1"));


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

    ui->textEdit_2->setReadOnly(true);

}

sparse::~sparse()
{
    delete ui;
}

void sparse::on_lineEdit_editingFinished()
{
    m_pTableModel->setTable(tr("sparse"));

    if (!ui->lineEdit->text().isEmpty())
    {
        m_pTableModel->setFilter(tr("cmdcode = '%1'").arg(ui->lineEdit->text()));
    }

    m_pTableModel->select();
}


void sparse::on_pushButton_clear_clicked()
{
    ui->textEdit_1->clear();
    ui->textEdit_2->clear();
}

void sparse::on_pushButton_Parse_clicked()
{
    QString scmd, result;

    scmd = ui->textEdit_1->toPlainText();

    scmdParse(scmd, result);

    ui->textEdit_2->setText(result);
}

/* 将网管下发的S口命令解析成容易查看的格式输出 */
void sparse::scmdParse(QString &scmd, QString &result)
{
    result = scmd;



}

void sparse::on_pushButtonAdd_clicked()
{
    qDebug() << "Add";
}

void sparse::on_pushButtonDel_clicked()
{
    qDebug() << "Del";
}

void sparse::on_pushButtonFind_clicked()
{
    QString cmdCode, cmdName, outerHead, innerHead, innerBody;
    QStringList outerHeadList, innerHeadList, innerBodyList;

    qDebug() << "Find";

    qDebug() << m_pTableModel->columnCount();
    qDebug() << m_pTableModel->rowCount();

    m_pTableModel->setFilter(tr("cmdcode = '%1'").arg(ui->lineEdit->text()));
    m_pTableModel->select();

    cmdCode = m_pTableModel->data(m_pTableModel->index(0,CMDCODE)).toString();
    cmdName = m_pTableModel->data(m_pTableModel->index(0,CMDNAME)).toString();
    outerHead = m_pTableModel->data(m_pTableModel->index(0,OUTERHEADLIST)).toString();
    innerHead = m_pTableModel->data(m_pTableModel->index(0,INNERHEADLIST)).toString();
    innerBody = m_pTableModel->data(m_pTableModel->index(0,INNERBODYLIST)).toString();

    qDebug() << cmdCode << cmdName << outerHead << innerHead << innerBody;

    outerHeadList = outerHead.split(",");
    innerHeadList = innerHead.split(",");
    innerBodyList = innerBody.split(",");

    qDebug() << outerHeadList;
    qDebug() << innerHeadList;
    qDebug() << innerBodyList;

    //将命令格式化



}
