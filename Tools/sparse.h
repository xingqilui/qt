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
    void on_pushButtonFind_clicked();

private:
    Ui::sparse *ui;

private:
    QSqlDatabase m_DB;
    QSqlTableModel *m_pTableModel;

};

#endif // SPARSE_H
