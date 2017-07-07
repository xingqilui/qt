#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sparse.h"
#include "ui_sparse.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Main Window"));

    //初始化菜单栏、工具栏、状态栏
    m_pActionNew    = new QAction(QIcon(":/images/new"), tr("New"), this);
    m_pActionOpen   = new QAction(QIcon(":/images/add"), tr("Open"), this);
    m_pActionSave   = new QAction(QIcon(":/images/love"), tr("Save"), this);

    m_pMenuStart = menuBar()->addMenu(tr("Start"));
    m_pMenuHelp = menuBar()->addMenu(tr("Help"));

    m_pToolBarFile = addToolBar(tr("File"));

    m_pMenuStart->addAction(m_pActionNew);
    m_pMenuStart->addAction(m_pActionOpen);
    m_pMenuStart->addAction(m_pActionSave);

    m_pToolBarFile->addAction(m_pActionNew);
    m_pToolBarFile->addAction(m_pActionOpen);
    m_pToolBarFile->addAction(m_pActionSave);

    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Click!";
}
