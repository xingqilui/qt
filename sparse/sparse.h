#ifndef SPARSE_H
#define SPARSE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class sparse;
}

class sparse : public QWidget
{
    Q_OBJECT

public:
    explicit sparse(QWidget *parent = 0);
    ~sparse();

private slots:
    void on_pushButton_parse_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_find_clicked();

private:
    Ui::sparse *ui;

private:
    QSqlDatabase m_DB;
    QSqlTableModel *m_pTableModel;

    int m_dstAddr = 4;
    int m_srcAddr = 4;
    int m_callId = 4;
    int m_cmdCode = 2;
    int m_reply = 1;
    int m_ExResult = 2;
    int m_reserved1 = 1;
    int m_msgLength = 4;
    int m_reserved2 = 2;

    void printLine(QString &dstStr, QString &srcStr, QString name, int &index, int length, QString &value);
    void printHead(QString &dstStr, QString &srcStr, QStringList &HeadList, int &index, int &num);
    void printBody(QString &dstStr, QString &srcStr, QStringList &HeadList, int &index);
    void scmdParse(QString &scmd, QString &result);
};

#endif // SPARSE_H
