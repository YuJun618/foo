#ifndef PLOTTESTDLG_H
#define PLOTTESTDLG_H

#include "qwt_plot_marker.h"
#include "qwt_plot_curve.h"
#include "qwt_plot.h"

#include <QDialog>

struct TPlotItem
{
    QwtPlot       *pPlot;
    QwtPlotMarker *pMark;
    QwtPlotCurve  *pCurve;
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

private:

    void drawFunctionSin( const TPlotItem &tPlotItem , double Vpp , double Freq , double Phase , double Period , double Offset );
    void drawFunctionPulse( const TPlotItem &tPlotItem ,double Vpp , double Freq ,  double Period  , double Offset, double width , double leading , double trailing );
    void drawFunctionModuAM( );

private:
    Ui::PlotTestDlg *ui;

    TPlotItem m_tPlotMain;
    TPlotItem m_tPlotModu;

//    QwtPlotMarker *m_pPlotOrigin1;
//    QwtPlotMarker *m_pPlotOrigin2;

//    QwtPlotCurve  *m_pPlotCurveChannel1;
//    QwtPlotCurve  *m_pPlotCurveChannel2;

//    double *m_pdzSampBufChannel1;
//    double *m_pdzSampCoordX;
};

#endif // PLOTTESTDLG_H
