#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

private:
    QSqlTableModel  *m_pTableModel;
    QSqlRelationalTableModel *m_pRelationTableModel;

    bool dbConnect(QString dbName);

    //query way
    bool tableCreate(QString tableName);
    bool tableDelete(QString tableName);
    bool tableUpdate(QString tableName);
    bool tableSelect(QString tableName);
    bool recordInsert(QString tableName, QString id, QString name, QString sex, QString age);
    bool recordModify(QString tableName, QString id, QString name, QString sex, QString age);
    bool recordDelete(QString tableName, QString id);

    //model way
    bool tableModelCreate(QString tableName);
    bool tableModelDelete(QString tableName);
    bool tableModelUpdate(QString tableName);
    bool tableModelSelect(QString tableName);
    bool recordModelInsert(QString tableName, QString id, QString name, QString sex, QString age);
    bool recordModelModify(QString tableName, QString id, QString name, QString sex, QString age);
    bool recordModelDelete(QString tableName, QString id);

};

#endif // WIDGET_H
