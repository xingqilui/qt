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
    //scmd = "0000010300000101006800011e19020000000000008e00000001000100c70080000b00420004000200000000000000410004000200000000000000450004000400000000000001460001000000010000000000490001000000020000000001450001000000640000000000480001000000c800000000004a00121100000000000000004b00120000000000ff0000004c00122200000000000000004d00120000000000ff0000";

    scmdParse(scmd, result);

    ui->textEdit_2->setText(result);
}

/* 将网管下发的S口命令解析成容易查看的格式输出 */

void sparse::printLine(QString &dstStr, QString &srcStr, QString name, int &index, int length, QString &value)
{
    value = srcStr.mid(index, length * 2);
    dstStr += name + value + "\n";
    index += length * 2;
}

void sparse::scmdParse(QString &scmd, QString &result)
{
    int index = 0, i = 0, j = 0, k = 0;
    int outerIndex, innerIndex;
    int outerNum = 0, innerNum = 0;
    bool ok;

    QString cmdCodeValue, cmdName, cmdLen, cmdValue;
    QString outerHeadValLen, innerHeadValLen, innerBodyValLen;
    QStringList outerHeadList, innerHeadList, innerBodyList, outerHeadValLenList, innerHeadValLenList, innerBodyValLenList;

    result += "====[MainHead]====\n";
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

    //cmdCode = m_pTableModel->data(m_pTableModel->index(0,CMDCODE)).toString();
    //cmdName = m_pTableModel->data(m_pTableModel->index(0,CMDNAME)).toString();
    outerHeadList = m_pTableModel->data(m_pTableModel->index(0, OUTERHEADLIST)).toString().split(",");
    innerHeadList = m_pTableModel->data(m_pTableModel->index(0, INNERHEADLIST)).toString().split(",");
    innerBodyList = m_pTableModel->data(m_pTableModel->index(0, INNERBODYLIST)).toString().split(",");

    result += "\n====[OuterHead]====\n";
    for (i = 0; i < outerHeadList.size(); i++)
    {
        outerHeadValLenList = outerHeadList[i].split(":");
        cmdName = outerHeadValLenList[VALUE] + ": ";
        cmdLen = outerHeadValLenList[LENGTH];

        printLine(result, scmd, cmdName, index, cmdLen.toInt(&ok, 16), cmdValue);
    }

    outerNum = cmdValue.toInt(&ok, 16);

    for (i = 0; i < outerNum; i++)
    {
        result += "\n====[InnerHead]====\n";
        for (j = 0; j < innerHeadList.size(); j++)
        {
            innerHeadValLenList = innerHeadList[j].split(":");
            cmdName = innerHeadValLenList[VALUE] + ": ";
            cmdLen = innerHeadValLenList[LENGTH];

            printLine(result, scmd, cmdName, index, cmdLen.toInt(&ok, 16), cmdValue);
        }

        innerNum = cmdValue.toInt(&ok, 16);

        for (innerIndex = 0; innerIndex < innerNum; innerIndex++)
        {
            result += "\n====[InnerBody]====\n";
            for (k = 0; k < innerBodyList.size(); k++)
            {
                innerBodyValLenList = innerBodyList[k].split(":");
                cmdName = innerBodyValLenList[VALUE] + ": ";
                cmdLen = innerBodyValLenList[LENGTH];

                printLine(result, scmd, cmdName, index, cmdLen.toInt(&ok, 16), cmdValue);
            }
        }
    }

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
