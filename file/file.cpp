#include <QFile>
#include <QDebug>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include "file.h"
#include "ui_file.h"

file::file(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::file)
{
    int ret = 0;
    int i = 0;
    int row = 0, col = 0;

    ui->setupUi(this);

    QFile file("5月份故障统计.txt");
    //QFile file("aaa.txt");

    QString content;
    QString content1;
    QString contentItem;
    QStringList contentItemList;


    ret = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!ret)
    {
        qDebug() << "Open file failed!";
        return;
    }

    while(!file.atEnd())
    {
        content += file.readLine();
    }

    ui->textEdit->setText(content);

    file.seek(0);

    contentItem = file.readLine();
    contentItem = contentItem.left(contentItem.length() - 1);
    contentItemList = contentItem.split('\t');



    for (i = 0; i < contentItemList.size(); i++)
    {
        content1 += contentItemList[i] + "\n";
    }
    ui->textEdit_2->setText(content1);
    //////////////////////////////////////////////////////////

    QString str = "1,2,3,4,5,6,7,8,9,0";
    QStringList strList;

    strList = str.split(",");

    for (i = 0; i < strList.size(); i++)
    {
        qDebug() << strList[i];
    }

    //////////////////////////////////////////////////////////
    QString tableRow;
    QStringList tableRowList;

    QStandardItemModel *pModel = new QStandardItemModel(this);
    pModel->setHorizontalHeaderLabels(contentItemList);

    for (row = 0; !file.atEnd(); row++)
    {
        tableRow = file.readLine();
        tableRow = tableRow.left(tableRow.length() - 1);

        tableRowList = tableRow.split('\t');

        for (col = 0; col < tableRowList.size(); col++)
        {
            pModel->setItem(row, col, new QStandardItem(tableRowList[col]));
        }
    }



    ui->tableView->setModel(pModel);

    return;
}

file::~file()
{
    delete ui;
}
