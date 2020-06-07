/********************************************************************************
** Form generated from reading UI file 'plottestdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTTESTDLG_H
#define UI_PLOTTESTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_PlotTestDlg
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QwtPlot *qwtPlot1;
    QwtPlot *qwtPlot2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox;

    void setupUi(QDialog *PlotTestDlg)
    {
        if (PlotTestDlg->objectName().isEmpty())
            PlotTestDlg->setObjectName(QStringLiteral("PlotTestDlg"));
        PlotTestDlg->resize(754, 446);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PlotTestDlg->sizePolicy().hasHeightForWidth());
        PlotTestDlg->setSizePolicy(sizePolicy);
        PlotTestDlg->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(PlotTestDlg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        qwtPlot1 = new QwtPlot(PlotTestDlg);
        qwtPlot1->setObjectName(QStringLiteral("qwtPlot1"));
        QBrush brush(QColor(240, 240, 240, 255));
        brush.setStyle(Qt::SolidPattern);
        qwtPlot1->setProperty("canvasBackground", QVariant(brush));
        qwtPlot1->setProperty("autoReplot", QVariant(false));

        verticalLayout_2->addWidget(qwtPlot1);

        qwtPlot2 = new QwtPlot(PlotTestDlg);
        qwtPlot2->setObjectName(QStringLiteral("qwtPlot2"));

        verticalLayout_2->addWidget(qwtPlot2);

        verticalLayout_2->setStretch(0, 5);
        verticalLayout_2->setStretch(1, 2);

        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(PlotTestDlg);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        comboBox = new QComboBox(PlotTestDlg);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_3->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(PlotTestDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        doubleSpinBox_2 = new QDoubleSpinBox(PlotTestDlg);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));

        horizontalLayout_2->addWidget(doubleSpinBox_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(PlotTestDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        doubleSpinBox = new QDoubleSpinBox(PlotTestDlg);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        horizontalLayout->addWidget(doubleSpinBox);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalLayout_4->setStretch(0, 5);
        horizontalLayout_4->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);


        retranslateUi(PlotTestDlg);

        QMetaObject::connectSlotsByName(PlotTestDlg);
    } // setupUi

    void retranslateUi(QDialog *PlotTestDlg)
    {
        PlotTestDlg->setWindowTitle(QApplication::translate("PlotTestDlg", "Dialog", 0));
        label->setText(QApplication::translate("PlotTestDlg", "\346\263\242\345\275\242\351\200\211\346\213\251", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("PlotTestDlg", "SIN", 0)
         << QApplication::translate("PlotTestDlg", "Pulse", 0)
        );
        label_2->setText(QApplication::translate("PlotTestDlg", "\351\242\221\347\216\207", 0));
        label_3->setText(QApplication::translate("PlotTestDlg", "\345\271\205\345\272\246", 0));
    } // retranslateUi

};

namespace Ui {
    class PlotTestDlg: public Ui_PlotTestDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTTESTDLG_H
