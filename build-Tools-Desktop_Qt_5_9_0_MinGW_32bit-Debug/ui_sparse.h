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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QLabel *label_1;
    QTextEdit *textEdit_1;
    QLabel *label;
    QTableView *tableView;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonFind;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonDel;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_Parse;
    QPushButton *pushButton_clear;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTextEdit *textEdit_2;

    void setupUi(QWidget *sparse)
    {
        if (sparse->objectName().isEmpty())
            sparse->setObjectName(QStringLiteral("sparse"));
        sparse->resize(616, 492);
        horizontalLayout_2 = new QHBoxLayout(sparse);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_1 = new QLabel(sparse);
        label_1->setObjectName(QStringLiteral("label_1"));

        verticalLayout->addWidget(label_1);

        textEdit_1 = new QTextEdit(sparse);
        textEdit_1->setObjectName(QStringLiteral("textEdit_1"));

        verticalLayout->addWidget(textEdit_1);

        label = new QLabel(sparse);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        tableView = new QTableView(sparse);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(tableView);

        lineEdit = new QLineEdit(sparse);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonFind = new QPushButton(sparse);
        pushButtonFind->setObjectName(QStringLiteral("pushButtonFind"));

        horizontalLayout->addWidget(pushButtonFind);

        pushButtonAdd = new QPushButton(sparse);
        pushButtonAdd->setObjectName(QStringLiteral("pushButtonAdd"));

        horizontalLayout->addWidget(pushButtonAdd);

        pushButtonDel = new QPushButton(sparse);
        pushButtonDel->setObjectName(QStringLiteral("pushButtonDel"));

        horizontalLayout->addWidget(pushButtonDel);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        pushButton_Parse = new QPushButton(sparse);
        pushButton_Parse->setObjectName(QStringLiteral("pushButton_Parse"));

        verticalLayout_3->addWidget(pushButton_Parse);

        pushButton_clear = new QPushButton(sparse);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));

        verticalLayout_3->addWidget(pushButton_clear);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(sparse);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        textEdit_2 = new QTextEdit(sparse);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));

        verticalLayout_2->addWidget(textEdit_2);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(sparse);

        QMetaObject::connectSlotsByName(sparse);
    } // setupUi

    void retranslateUi(QWidget *sparse)
    {
        sparse->setWindowTitle(QApplication::translate("sparse", "Form", Q_NULLPTR));
        label_1->setText(QApplication::translate("sparse", "S_cmd", Q_NULLPTR));
        label->setText(QApplication::translate("sparse", "Support list", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("sparse", "Input cmdCode Enter...", Q_NULLPTR));
        pushButtonFind->setText(QApplication::translate("sparse", "Find", Q_NULLPTR));
        pushButtonAdd->setText(QApplication::translate("sparse", "Add", Q_NULLPTR));
        pushButtonDel->setText(QApplication::translate("sparse", "Del", Q_NULLPTR));
        pushButton_Parse->setText(QApplication::translate("sparse", "Parse ->", Q_NULLPTR));
        pushButton_clear->setText(QApplication::translate("sparse", "Clear", Q_NULLPTR));
        label_2->setText(QApplication::translate("sparse", "S Infomation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sparse: public Ui_sparse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPARSE_H
