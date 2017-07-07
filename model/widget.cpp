#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QAbstractItemView>
#include <QMessageBox>
#include <QDebug>
#include <QList>
#include <QStringList>
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    bool ret = true;

    ui->setupUi(this);


    dbConnect("model.db");

    tableDelete("student");
    tableDelete("teacher");

    tableCreate("student");
    tableCreate("teacher");


    //tableUpdate("student");
    //tableSelect("student");

    ret |= recordInsert("student", "1", "Chenlei", "male", "30");
    ret |= recordInsert("student", "2", "Chenlei3", "male", "31");
    ret |= recordInsert("student", "3", "Chenlei4", "male", "32");
    ret |= recordInsert("student", "4", "Chenlei5", "male", "33");
    ret |= recordInsert("student", "5", "Chenlei6", "male", "34");

    //ret |= recordDelete("student", "1");
    //ret |= recordDelete("student", "2");

    //ret |= recordModify("student", "5", "Chenlei10", "male", "35");

    if (true != ret)
    {
        QMessageBox::information(this, "Info", "Insert record failed!");
    }

    m_pTableModel = new QSqlTableModel;
    m_pTableModel->setTable("people");
    m_pTableModel->setSort(0, Qt::AscendingOrder);
    m_pTableModel->select();

    m_pRelationTableModel = new QSqlRelationalTableModel(this);
    m_pRelationTableModel->setTable("people");
    m_pRelationTableModel->setSort(0, Qt::AscendingOrder);
    m_pRelationTableModel->setRelation(5, QSqlRelation("city", "id", "name"));
    m_pRelationTableModel->select();

    ui->tableView->setModel(m_pRelationTableModel);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

#if 0
    //Connect sql
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("feature.db");

    if (!db.open())
    {
        qDebug() << "db open failed!";
    }

    QSqlTableModel *pModelFeature = new QSqlTableModel;
    pModelFeature->setTable("feature");
    pModelFeature->setSort(2, Qt::DescendingOrder);
    pModelFeature->select();

    ui->tableView_1->setModel(pModelFeature);
    ui->tableView_1->resizeColumnsToContents();

    QSqlTableModel *pModelStory = new QSqlTableModel;
    pModelStory->setTable("story");
    pModelStory->setSort(1, Qt::AscendingOrder);
    pModelStory->setHeaderData(1, Qt::Horizontal, "ID");
    pModelStory->setHeaderData(2, Qt::Horizontal, "Titel");
    pModelStory->select();

    ui->tableView_2->setModel(pModelStory);


    //ui->tableView_1->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView_1->setSelectionBehavior(QAbstractItemView::SelectRows);
    //
    //ui->tableView_1->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQueryModel *pModel = new QSqlQueryModel(ui->tableView_1);
    pModel->sele
    pModel->setQuery(QString("select * from featrue"));
    pModel->setHeaderData(0, Qt::Horizontal, tr("序号"));
    pModel->setHeaderData(1, Qt::Horizontal, tr("标题"));
    pModel->setHeaderData(2, Qt::Horizontal, tr("内容"));
    ui->tableView_1->setModel(pModel);


    m_pTableModel = new QStandardItemModel(20, 3);
    m_pTableModel->setHorizontalHeaderLabels(QStringList() << "Name" << "Class" << "Age");

    ui->tableView_1->setModel(m_pTableModel);
    ui->tableView_1->horizontalHeader()->setAlternatingRowColors(true);
    ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView_2->setModel(m_pTableModel);
#endif

}

Widget::~Widget()
{
    delete ui;
}

bool Widget::dbConnect(QString dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(dbName);
    db.setDatabaseName(dbName);

    return db.open();
}

bool Widget::tableCreate(QString tableName)
{
    QSqlQuery query;
    query.exec("CREATE TABLE " + tableName + " (Id varchar(8) primary key, Name varchar(20), Sex varchar(8), Age integer(2)) WITHOUT ROWID");
    return true;
}

bool Widget::tableDelete(QString tableName)
{
    QSqlQuery query;
    query.exec("DROP TABLE " + tableName);
    return true;
}

bool Widget::tableUpdate(QString tableName)
{
    QSqlQuery query;
    query.exec("UPDATE TABLE " + tableName);
    return true;
}

bool Widget::tableSelect(QString tableName)
{
    QSqlQuery query;
    query.exec("SELECT * FROM " + tableName);
    return true;
}

bool Widget::recordInsert(QString tableName, QString id, QString name, QString sex, QString age)
{
    QSqlQuery query;
    QString sql;

    sql = QString("INSERT INTO %1 (Id, Name, Sex, Age) VALUES ('%2', '%3', '%4', %5)")
            .arg(tableName).arg(id).arg(name).arg(sex).arg(age);

    query.exec(sql);
    return true;
}

bool Widget::recordModify(QString tableName, QString id, QString name, QString sex, QString age)
{
    QSqlQuery query;
    QString sql;

    sql = QString("UPDATE %1 SET Name = '%3', Sex = '%4', Age = %5 WHERE Id ='%2'")
            .arg(tableName).arg(id).arg(name).arg(sex).arg(age);

    query.exec(sql);
    return true;
}

bool Widget::recordDelete(QString tableName, QString id)
{
    QSqlQuery query;
    QString sql;

    sql = QString("DELETE FROM %1 WHERE Id = '%2'")
            .arg(tableName).arg(id);

    query.exec(sql);
    return true;
}

