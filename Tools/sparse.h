#ifndef SPARSE_H
#define SPARSE_H

#include <QWidget>

namespace Ui {
class sparse;
}

class sparse : public QWidget
{
    Q_OBJECT

public:
    explicit sparse(QWidget *parent = 0);
    ~sparse();

private:
    Ui::sparse *ui;
};

#endif // SPARSE_H
