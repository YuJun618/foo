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

struct TWaveFormParamDigital
{
    double symbolRate; // 符号速率
    double interPoint; // 插值个数
    double filterType; // 符号成型滤波类型
    double filterCoeff; // 符号系数
    int    polar; // 是否极性
    char*  symbolBuf;  // 符号
    int    symbolCount; // 符号数量
    TWaveFormParamDigital()
    {
        this->symbolRate = 0;
        this->interPoint = 0;
        this->filterType = 0;
        this->filterCoeff = 0;
        this->polar = 0;
        this->symbolBuf  = NULL;
        this->symbolCount = 0;
    }

    TWaveFormParamDigital( double symbolRate, double interPoint,double filterType,double filterCoeff, int    polar)
    {
        this->symbolRate = symbolRate;
        this->interPoint = interPoint;
        this->filterType = filterType;
        this->filterCoeff = filterCoeff;
        this->polar = polar;
        this->symbolBuf  = NULL;
        this->symbolCount = 0;
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
    friend class RealScaleDraw;

    Q_OBJECT

public:
    explicit PlotTestDlg(QWidget *parent = 0);
    ~PlotTestDlg();

public:

    // 绘制正弦波
    static void drawFunctionSin( const TPlotItem &tPlotItem , const TWaveFormParamBase &tWaveParam , int nDrawPeriodCount );

    // 绘制脉冲波形
    static void drawFunctionPulse( const TPlotItem &tPlotItem , const TWaveFormParamPulse &tWaveParam , int nDrawPeriodCount );

    // 绘制数字信号
    static void drawFuncitonDigital( const TPlotItem &tPlotItem , const TWaveFormParamDigital &tWaveParam );

    // 绘制调幅波形
    static void drawFunctionModuAM( const TPlotItem &tPlotItem ,
                                    const TWaveFormParamBase &tWaveParamModuSig , int nDrawPeriodModuSigCount,
                                    const TWaveFormParamBase &tWaveParamCarrierSig , int nDrawPeriodCarrierSigCount);

    // 绘制调频波形
    static void drawFunctionModuFM( const TPlotItem &tPlotItem ,
                                    const TWaveFormParamBase &tWaveParamModuSig , int nDrawPeriodModuSigCount,
                                    const TWaveFormParamBase &tWaveParamCarrierSig , int nDrawPeriodCarrierSigCount,
                                    double dDCoef );

    // 绘制调相波形
    static void drawFunctionModuPM( const TPlotItem &tPlotItem ,
                                    const TWaveFormParamBase &tWaveParamModuSig , int nDrawPeriodModuSigCount,
                                    const TWaveFormParamBase &tWaveParamCarrierSig , int nDrawPeriodCarrierSigCount,
                                    double dDCoef );

    // 绘制脉调波形
    static void drawFunctionModuPulse( const TPlotItem &tPlotItem ,
                                       const TWaveFormParamPulse &tWaveParamModuSig , int nDrawPeriodModuSigCount,
                                       const TWaveFormParamBase &tWaveParamCarrierSig );

    // 绘制ASK波形
    static void drawFunctionModuASK( const TPlotItem &tPlotItem ,
                                     const TWaveFormParamDigital &tWaveParamModuSig ,
                                     const TWaveFormParamBase &tWaveParamCarrierSig  );

    // 绘制FSK波形
    static void drawFunctionModuFSK( const TPlotItem &tPlotItem ,
                                     const TWaveFormParamDigital &tWaveParamModuSig ,
                                     const TWaveFormParamBase &tWaveParamCarrierSig ,
                                     double f1 );

    // 绘制PSK波形
    static void drawFunctionModuPSK( const TPlotItem &tPlotItem ,
                                     const TWaveFormParamDigital &tWaveParamModuSig ,
                                     const TWaveFormParamBase &tWaveParamCarrierSig );

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void paramChanged(double);
    void paramChanged();


    void on_cbBitSeq_clicked(bool checked);

    void on_sbDModuBitCount_valueChanged(int arg1);

private:

    void getParamBase( TWaveFormParamBase &tWaveParamModuSig );
    void getParamAModu(TWaveFormParamBase &tWaveParamModuSig );
    void getParamPulse( TWaveFormParamPulse &tWaveParamPulse );
    void getParamDigit( TWaveFormParamDigital &tWaveParamDitital );

    void initBitSequenceTableView();

private:
    Ui::PlotTestDlg *ui;

    TPlotItem m_tPlotMain;
    TPlotItem m_tPlotModu;

};

#endif // PLOTTESTDLG_H
