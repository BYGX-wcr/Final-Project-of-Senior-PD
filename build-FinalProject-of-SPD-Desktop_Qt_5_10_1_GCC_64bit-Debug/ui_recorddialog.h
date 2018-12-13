/********************************************************************************
** Form generated from reading UI file 'recorddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDDIALOG_H
#define UI_RECORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_RecordDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_4;
    QDateEdit *dateEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_5;

    void setupUi(QDialog *RecordDialog)
    {
        if (RecordDialog->objectName().isEmpty())
            RecordDialog->setObjectName(QStringLiteral("RecordDialog"));
        RecordDialog->resize(579, 503);
        buttonBox = new QDialogButtonBox(RecordDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(70, 390, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(RecordDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(190, 40, 101, 30));
        lineEdit_2 = new QLineEdit(RecordDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(190, 90, 101, 30));
        lineEdit_4 = new QLineEdit(RecordDialog);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(190, 240, 131, 30));
        dateEdit = new QDateEdit(RecordDialog);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setGeometry(QRect(190, 190, 133, 31));
        label = new QLabel(RecordDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 40, 51, 22));
        label_2 = new QLabel(RecordDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 90, 51, 22));
        label_3 = new QLabel(RecordDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(130, 140, 51, 22));
        comboBox = new QComboBox(RecordDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(190, 140, 101, 30));
        label_4 = new QLabel(RecordDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 190, 51, 22));
        label_5 = new QLabel(RecordDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(130, 240, 51, 22));
        label_6 = new QLabel(RecordDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(130, 290, 51, 22));
        lineEdit_5 = new QLineEdit(RecordDialog);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(190, 290, 181, 30));

        retranslateUi(RecordDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RecordDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RecordDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RecordDialog);
    } // setupUi

    void retranslateUi(QDialog *RecordDialog)
    {
        RecordDialog->setWindowTitle(QApplication::translate("RecordDialog", "Dialog", nullptr));
        lineEdit->setText(QString());
        label->setText(QApplication::translate("RecordDialog", "\345\255\246\345\217\267\357\274\232", nullptr));
        label_2->setText(QApplication::translate("RecordDialog", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_3->setText(QApplication::translate("RecordDialog", "\346\200\247\345\210\253\357\274\232", nullptr));
        label_4->setText(QApplication::translate("RecordDialog", "\347\224\237\346\227\245\357\274\232", nullptr));
        label_5->setText(QApplication::translate("RecordDialog", "\347\261\215\350\264\257\357\274\232", nullptr));
        label_6->setText(QApplication::translate("RecordDialog", "\344\275\217\345\235\200\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecordDialog: public Ui_RecordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDDIALOG_H
