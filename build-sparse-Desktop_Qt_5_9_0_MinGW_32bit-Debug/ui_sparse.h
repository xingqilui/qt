/********************************************************************************
** Form generated from reading UI file 'sparse.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPARSE_H
#define UI_SPARSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sparse
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *textEdit_scmd;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_parse;
    QPushButton *pushButton_clear;
    QFrame *line;
    QLabel *label_2;
    QTableView *tableView;
    QGridLayout *gridLayout;
    QPushButton *pushButton_add;
    QPushButton *pushButton_find;
    QLineEdit *lineEdit;
    QPushButton *pushButton_del;
    QPushButton *pushButton_mod;
    QPushButton *pushButton_update;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QTextEdit *textEdit_result;

    void setupUi(QWidget *sparse)
    {
        if (sparse->objectName().isEmpty())
            sparse->setObjectName(QStringLiteral("sparse"));
        sparse->resize(911, 631);
        horizontalLayout_2 = new QHBoxLayout(sparse);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(sparse);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        textEdit_scmd = new QTextEdit(sparse);
        textEdit_scmd->setObjectName(QStringLiteral("textEdit_scmd"));

        verticalLayout->addWidget(textEdit_scmd);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_parse = new QPushButton(sparse);
        pushButton_parse->setObjectName(QStringLiteral("pushButton_parse"));

        horizontalLayout->addWidget(pushButton_parse);

        pushButton_clear = new QPushButton(sparse);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));

        horizontalLayout->addWidget(pushButton_clear);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(sparse);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label_2 = new QLabel(sparse);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        tableView = new QTableView(sparse);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_add = new QPushButton(sparse);
        pushButton_add->setObjectName(QStringLiteral("pushButton_add"));

        gridLayout->addWidget(pushButton_add, 1, 0, 1, 1);

        pushButton_find = new QPushButton(sparse);
        pushButton_find->setObjectName(QStringLiteral("pushButton_find"));

        gridLayout->addWidget(pushButton_find, 0, 3, 1, 1);

        lineEdit = new QLineEdit(sparse);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 3);

        pushButton_del = new QPushButton(sparse);
        pushButton_del->setObjectName(QStringLiteral("pushButton_del"));

        gridLayout->addWidget(pushButton_del, 1, 1, 1, 1);

        pushButton_mod = new QPushButton(sparse);
        pushButton_mod->setObjectName(QStringLiteral("pushButton_mod"));

        gridLayout->addWidget(pushButton_mod, 1, 2, 1, 1);

        pushButton_update = new QPushButton(sparse);
        pushButton_update->setObjectName(QStringLiteral("pushButton_update"));

        gridLayout->addWidget(pushButton_update, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(sparse);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        textEdit_result = new QTextEdit(sparse);
        textEdit_result->setObjectName(QStringLiteral("textEdit_result"));

        verticalLayout_3->addWidget(textEdit_result);


        horizontalLayout_2->addLayout(verticalLayout_3);


        retranslateUi(sparse);

        QMetaObject::connectSlotsByName(sparse);
    } // setupUi

    void retranslateUi(QWidget *sparse)
    {
        sparse->setWindowTitle(QApplication::translate("sparse", "sparse", Q_NULLPTR));
        label->setText(QApplication::translate("sparse", "S Cmd", Q_NULLPTR));
        pushButton_parse->setText(QApplication::translate("sparse", "Parse", Q_NULLPTR));
        pushButton_clear->setText(QApplication::translate("sparse", "Clear", Q_NULLPTR));
        label_2->setText(QApplication::translate("sparse", "Support Cmd List", Q_NULLPTR));
        pushButton_add->setText(QApplication::translate("sparse", "Add", Q_NULLPTR));
        pushButton_find->setText(QApplication::translate("sparse", "Find", Q_NULLPTR));
        lineEdit->setInputMask(QString());
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QApplication::translate("sparse", "Input scmd Enter...", Q_NULLPTR));
        pushButton_del->setText(QApplication::translate("sparse", "Del", Q_NULLPTR));
        pushButton_mod->setText(QApplication::translate("sparse", "Mod", Q_NULLPTR));
        pushButton_update->setText(QApplication::translate("sparse", "Update", Q_NULLPTR));
        label_3->setText(QApplication::translate("sparse", "S Infomation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sparse: public Ui_sparse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPARSE_H
