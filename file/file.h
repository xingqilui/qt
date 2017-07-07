#ifndef FILE_H
#define FILE_H

#include <QWidget>

namespace Ui {
class file;
}

class file : public QWidget
{
    Q_OBJECT

public:
    explicit file(QWidget *parent = 0);
    ~file();

private:
    Ui::file *ui;

private:

};

#endif // FILE_H
