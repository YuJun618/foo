#include "dialog.h"
#include "ui_dialog.h"
#include "switchcontrol.h"
#include <QVBoxLayout>

#include "plottestdlg.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
//    connect(ui->label , SIGNAL(click()) , ui->pushButton , SLOT(click()));


//    QVBoxLayout *pLayout = new QVBoxLayout(this);
//    SwitchControl *pSwitchControl = new SwitchControl(this);
//    SwitchControl *pGreenSwitchControl = new SwitchControl(this);
//    SwitchControl *pDisabledSwitchControl = new SwitchControl(this);
//    pLayout->addWidget( pSwitchControl );
//    pLayout->addWidget( pGreenSwitchControl );
//    pLayout->addWidget( pDisabledSwitchControl );

//    // 设置状态、样式
//    pGreenSwitchControl->setToggle(true);
//    pGreenSwitchControl->setCheckedColor(QColor(0, 160, 230));
//    pDisabledSwitchControl->setDisabled(true);
//    pDisabledSwitchControl->setToggle(true);
//    ui->groupBox->setLayout(pLayout );

//    // 连接信号槽
//    connect(pSwitchControl, SIGNAL(toggled(bool)), this, SLOT(onToggled(bool)));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    PlotTestDlg *pDlg = new PlotTestDlg(this);
    pDlg->show();
}
