#ifndef PLOTTESTDLG_H
#define PLOTTESTDLG_H

#include "qwt_plot_marker.h"
#include "qwt_plot_curve.h"
#include "qwt_plot.h"

#include <QDialog>

struct TWaveFormParamBase
{
    double Vpp; // 峰峰值（V）
    double Phase; // 相位（°）
    double Period; // 实际周期（ns-纳秒）
    double Offset; // 偏置（V）
    TWaveFormParamBase()
    {
        Vpp = 0;
        Phase = 0;
        Period = 0;
        Offset = 0;
    }

    TWaveFormParamBase( double Vpp, double Phase,  double Period , double Offset )
    {
        this->Vpp = Vpp;
        this->Phase = Phase;
        this->Period = Period;
        this->Offset = Offset;
    }
};

struct TWaveFormParamPulse: public TWaveFormParamBase
{
    double width; // 脉宽（ns-纳秒）
    double leading; // 上升沿（ns-纳秒）
    double trailing; // 下降沿（ns-纳秒）
    TWaveFormParamPulse():TWaveFormParamBase()
    {
        width = 0;
        leading = 0;
        trailing = 0;
    }

    TWaveFormParamPulse( double Vpp, double Phase,  double Period , double Offset ,
                         double width , double leading , double trailing ):TWaveFormParamBase(Vpp, Phase,  Period , Offset )
    {
        this->width = width;
        this->leading = leading;
        this->trailing = trailing;
    }
};

struct TDModuParam
{

};

struct TPModuParam
{

};

class RealScaleDraw;

struct TPlotItem
{
    QwtPlot       *pPlot;
    QwtPlotMarker *pMark;
    QwtPlotCurve  *pCurve;
    RealScaleDraw *pScaleDraw;
    double        *y;
    double        *x;
};

namespace Ui {
class PlotTestDlg;
}

class PlotTestDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PlotTestDlg(QWidget *parent = 0);
    ~PlotTestDlg();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void paramChanged(double);

private:

    // 绘制正弦波
    void drawFunctionSin( const TPlotItem &tPlotItem , const TWaveFormParamBase &tWaveParam , int nDrawPeriodCount );

    // 绘制脉冲波形
    void drawFunctionPulse( const TPlotItem &tPlotItem , const TWaveFormParamPulse &tWaveParam , int nDrawPeriodCount );

    // 绘制调幅波形
    void drawFunctionModuAM( const TPlotItem &tPlotItem ,
                             const TWaveFormParamBase &tWaveParamModuSig , int nDrawPeriodModuSigCount,
                             const TWaveFormParamBase &tWaveParamCarrierSig , int nDrawPeriodCarrierSigCount);

    // 绘制调频波形
    void drawFunctionModuFM( const TPlotItem &tPlotItem ,
                             const TWaveFormParamBase &tWaveParamModuSig , int nDrawPeriodModuSigCount,
                             const TWaveFormParamBase &tWaveParamCarrierSig , int nDrawPeriodCarrierSigCount,
                             double dDCoef );

    // 绘制调相波形
    void drawFunctionModuPM( const TPlotItem &tPlotItem ,
                             const TWaveFormParamBase &tWaveParamModuSig , int nDrawPeriodModuSigCount,
                             const TWaveFormParamBase &tWaveParamCarrierSig , int nDrawPeriodCarrierSigCount,
                             double dDCoef );

    // 绘制脉调波形
    void drawFunctionModuPulse( const TPlotItem &tPlotItem ,
                                const TWaveFormParamPulse &tWaveParamModuSig , int nDrawPeriodModuSigCount,
                                const TWaveFormParamBase &tWaveParamCarrierSig , int nDrawPeriodCarrierSigCount );

    void getParamBase( TWaveFormParamBase &tWaveParamModuSig );
    void getParamAModu(TWaveFormParamBase &tWaveParamModuSig );
    void getParamPulse( TWaveFormParamPulse &tWaveParamPulse );

    void initBitSequenceTableView();

private:
    Ui::PlotTestDlg *ui;

    TPlotItem m_tPlotMain;
    TPlotItem m_tPlotModu;

};

#endif // PLOTTESTDLG_H
