#include <QMessageBox>
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

enum
{
    VALUE,
    LENGTH,
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
        QMessageBox::information(this, "Info", "DB open failed!");
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

    ui->textEdit_result->setReadOnly(true);
}

sparse::~sparse()
{
    delete ui;
}

void sparse::printLine(QString &dstStr, QString &srcStr, QString name, int &index, int length, QString &value)
{
    value = srcStr.mid(index, length * 2);
    dstStr += name + value + "\n";
    index += length * 2;
}

void sparse::printHead(QString &dstStr, QString &srcStr, QStringList &HeadList, int &index, int &num)
{
    QString cmdName, cmdLen, cmdValue;
    QStringList headValLenList;
    bool ok;
    int i;

    for (i = 0; i < HeadList.size(); i++)
    {
        headValLenList = HeadList[i].split(":");
        cmdName = headValLenList[VALUE] + ": ";
        cmdLen = headValLenList[LENGTH];

        printLine(dstStr, srcStr, cmdName, index, cmdLen.toInt(&ok, 16), cmdValue);
    }

    num = cmdValue.toInt(&ok, 16);
}

void sparse::printBody(QString &dstStr, QString &srcStr, QStringList &HeadList, int &index)
{
    QString cmdName, cmdLen, cmdValue;
    QStringList headValLenList;
    bool ok;
    int i;

    for (i = 0; i < HeadList.size(); i++)
    {
        headValLenList = HeadList[i].split(":");
        cmdName = headValLenList[VALUE] + ": ";
        cmdLen = headValLenList[LENGTH];

        printLine(dstStr, srcStr, cmdName, index, cmdLen.toInt(&ok, 16), cmdValue);
    }
}

void sparse::scmdParse(QString &scmd, QString &result)
{
    int index = 0, outerIndex = 0, innerIndex = 0, outerNum = 0, innerNum = 0;

    QString cmdCodeValue, cmdValue;
    QStringList outerHeadList, innerHeadList, innerBodyList;

    result += "==========[MainHead]==========\n";
    printLine(result, scmd, "DstAddr: ", index, m_dstAddr, cmdValue);
    printLine(result, scmd, "SrcAddr: ", index, m_srcAddr, cmdValue);
    printLine(result, scmd, "CallId: ", index, m_callId, cmdValue);
    printLine(result, scmd, "CmdCode: ", index, m_cmdCode, cmdCodeValue);
    printLine(result, scmd, "Reply: ", index, m_reply, cmdValue);
    printLine(result, scmd, "ExResult: ", index, m_ExResult, cmdValue);
    printLine(result, scmd, "Reserved1: ", index, m_reserved1, cmdValue);
    printLine(result, scmd, "MsgLength: ", index, m_msgLength, cmdValue);
    printLine(result, scmd, "Reserved2: ", index, m_reserved2, cmdValue);

    m_pTableModel->setFilter(tr("cmdcode = '%1'").arg(cmdCodeValue));
    m_pTableModel->select();

    outerHeadList = m_pTableModel->data(m_pTableModel->index(0, OUTERHEADLIST)).toString().split(",");
    innerHeadList = m_pTableModel->data(m_pTableModel->index(0, INNERHEADLIST)).toString().split(",");
    innerBodyList = m_pTableModel->data(m_pTableModel->index(0, INNERBODYLIST)).toString().split(",");

    result += "\n==========[OuterHead]==========\n";
    printHead(result, scmd, outerHeadList, index, outerNum);

    for (outerIndex = 0; outerIndex < outerNum; outerIndex++)
    {
        result += "\n====[InnerHead]====\n";
        printHead(result, scmd, innerHeadList, index, innerNum);

        for (innerIndex = 0; innerIndex < innerNum; innerIndex++)
        {
            result += "\n====[InnerBody]====\n";
            printBody(result, scmd, innerBodyList, index);
        }
    }
}

void sparse::on_pushButton_parse_clicked()
{
    QString scmd, result;

    scmd = ui->textEdit_scmd->toPlainText();
    scmdParse(scmd, result);
    ui->textEdit_result->setText(result);
}

void sparse::on_pushButton_clear_clicked()
{
    ui->textEdit_scmd->clear();
    ui->textEdit_result->clear();
}

void sparse::on_pushButton_find_clicked()
{
    if (!ui->lineEdit->text().isEmpty())
    {
        m_pTableModel->setFilter(tr("cmdcode = '%1'").arg(ui->lineEdit->text()));
    }
    else
    {
        m_pTableModel->setFilter(tr(""));
    }

    m_pTableModel->select();
}
