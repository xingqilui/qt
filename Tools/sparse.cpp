#include "sparse.h"
#include "ui_sparse.h"

sparse::sparse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sparse)
{
    ui->setupUi(this);
}

sparse::~sparse()
{
    delete ui;
}
