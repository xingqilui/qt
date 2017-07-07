#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QMenu *m_pMenuStart;
    QMenu *m_pMenuHelp;

    QToolBar *m_pToolBarFile;

    QAction *m_pActionNew;
    QAction *m_pActionOpen;
    QAction *m_pActionSave;
};

#endif // MAINWINDOW_H
