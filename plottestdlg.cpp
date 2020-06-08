#include "plottestdlg.h"
#include "ui_plottestdlg.h"

#include "qwt_series_data.h"
#include "qwt_plot_canvas.h"
#include "qwt_painter.h"
#include "qwt_plot_grid.h"
#include "math.h"
#include "qwt_scale_draw.h"
#include "qwt_scale_widget.h"

#define PT_NUM 10000

class RealScaleDraw: public QwtScaleDraw
{
public:
    RealScaleDraw()
    {
        m_dCoef = 1.0;
    }

    void setCoef( double dCoef )
    {
        m_dCoef = dCoef;
    }

    virtual QwtText label(double v) const
    {
        return QwtText(QString::number(v*m_dCoef)); //60和120都除以10
    }

private:

    double m_dCoef;

};

class Canvas: public QwtPlotCanvas
{
public:
    Canvas( QwtPlot *plot = NULL ):
        QwtPlotCanvas( plot )
    {
        // The backing store is important, when working with widget
        // overlays ( f.e rubberbands for zooming ).
        // Here we don't have them and the internal
        // backing store of QWidget is good enough.

        setPaintAttribute( QwtPlotCanvas::HackStyledBackground, false );
        // 设置圆角
//        setBorderRadius( 10 );

        if ( QwtPainter::isX11GraphicsSystem() )
        {
#if QT_VERSION < 0x050000
            // Even if not liked by the Qt development, Qt::WA_PaintOutsidePaintEvent
            // works on X11. This has a nice effect on the performance.

            setAttribute( Qt::WA_PaintOutsidePaintEvent, true );
#endif

            // Disabling the backing store of Qt improves the performance
            // for the direct painter even more, but the canvas becomes
            // a native window of the window system, receiving paint events
            // for resize and expose operations. Those might be expensive
            // when there are many points and the backing store of
            // the canvas is disabled. So in this application
            // we better don't disable both backing stores.

            if ( testPaintAttribute( QwtPlotCanvas::BackingStore ) )
            {
                setAttribute( Qt::WA_PaintOnScreen, true );
                setAttribute( Qt::WA_NoSystemBackground, true );
            }
        }

        setupPalette();

        this->setFrameShadow(QFrame::Plain);
    }

private:
    void setupPalette()
    {
        QPalette pal = palette();

#if QT_VERSION >= 0x040400
        QLinearGradient gradient;
        gradient.setCoordinateMode( QGradient::StretchToDeviceMode );
        gradient.setColorAt( 0.0, QColor( 0, 49, 110 ) );
        gradient.setColorAt( 1.0, QColor( 0, 87, 174 ) );

        pal.setBrush( QPalette::Window, QBrush( QColor(0,0,0) /*gradient*/ ) );
#else
        pal.setBrush( QPalette::Window, QBrush( color ) );
#endif

        // QPalette::WindowText is used for the curve color
 //        pal.setColor( QPalette::WindowText, Qt::green );

        setPalette( pal );

 //       this->setStyleSheet( "border-color: rgb(255, 255, 255);");
    }
};


class CurveData: public QwtSeriesData<QPointF>
{
public:

    virtual QPointF sample( size_t i ) const
    {
        return m_vecPoints[i];
    }

    virtual size_t size() const
    {
        return m_vecPoints.size();
    }

    virtual QRectF boundingRect() const
    {
        return QRectF();
    }

public:

    QVector<QPointF> m_vecPoints;

};

PlotTestDlg::PlotTestDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotTestDlg)
{
    ui->setupUi(this);

    m_tPlotMain.x = new double[PT_NUM];
    m_tPlotMain.y = new double[PT_NUM];

    m_tPlotModu.x = new double[PT_NUM];
    m_tPlotModu.y = new double[PT_NUM];

    m_tPlotMain.pPlot = ui->qwtPlot1;
    m_tPlotModu.pPlot = ui->qwtPlot2;


//  m_tPlotMain.pPlot->setTitle( "Plot test" );
    m_tPlotMain.pPlot->setCanvas( new Canvas );
    m_tPlotMain.pPlot->setAxisScale( QwtPlot::xBottom, 0, 2  );
    m_tPlotMain.pPlot->setAxisScale( QwtPlot::yLeft, -1, 1 );
    m_tPlotMain.pPlot->enableAxis( QwtPlot::xBottom , false );
    m_tPlotMain.pPlot->enableAxis( QwtPlot::yLeft , false );
    m_tPlotMain.pScaleDraw = new RealScaleDraw();
    m_tPlotMain.pPlot->setAxisScaleDraw( QwtPlot::xBottom, m_tPlotMain.pScaleDraw );

 // ui->qwtPlot2->setTitle( "Plot test" );
    m_tPlotModu.pPlot->setCanvas( new Canvas );
 // ui->qwtPlot2->setAxisTitle( QwtPlot::xBottom, "Samp Point" );
    m_tPlotModu.pPlot->setAxisScale( QwtPlot::xBottom, 0, 2  );
    m_tPlotModu.pPlot->setAxisScale( QwtPlot::yLeft, -1, 1 );
    m_tPlotModu.pPlot->enableAxis( QwtPlot::yLeft , false );

    QList<double> ticks[QwtScaleDiv::NTickTypes];
    ticks[QwtScaleDiv::MajorTick] << 0 << 1 << 2;  //只在60和120个sample点tick
    QwtScaleDiv scaleDiv( ticks[QwtScaleDiv::MajorTick].first(),
                          ticks[QwtScaleDiv::MajorTick].last(),
                          ticks );
    m_tPlotModu.pPlot->setAxisScaleDiv( QwtPlot::xBottom, scaleDiv);
    m_tPlotModu.pScaleDraw = new RealScaleDraw();
    m_tPlotModu.pPlot->setAxisScaleDraw( QwtPlot::xBottom, m_tPlotModu.pScaleDraw );
//    m_tPlotMain.pPlot->setAxisScaleDiv(QwtPlot::xBottom, scaleDiv);


//    m_pPlot->enableAxis( QwtPlot::xBottom , false );
//    m_pPlot->enableAxis( QwtPlot::yLeft , false );
//    m_pPlot->setLineWidth(2);

    // 网格设置
//    QwtPlotGrid *grid = new QwtPlotGrid();
//    grid->setPen( Qt::gray, 0.0, Qt::DotLine );
//    grid->enableX( true );
//    grid->enableXMin( true );
//    grid->enableY( true );
//    grid->enableYMin( false );
//    grid->attach( qwtPlot );

//    grid->setXDiv( QwtScaleDiv( 0 , 100 ) );

    // 原点设置
    m_tPlotMain.pMark = new QwtPlotMarker();
    m_tPlotMain.pMark->setLineStyle( QwtPlotMarker::Cross );
    m_tPlotMain.pMark->setLinePen( Qt::gray, 0.0, Qt::DashLine );
    m_tPlotMain.pMark->attach( m_tPlotMain.pPlot );

    m_tPlotModu.pMark = new QwtPlotMarker();
    m_tPlotModu.pMark->setLineStyle( QwtPlotMarker::Cross );
    m_tPlotModu.pMark->setLinePen( Qt::gray, 0.0, Qt::DashLine );
    m_tPlotModu.pMark->attach( m_tPlotModu.pPlot );

    // 通道1曲线初始化
    m_tPlotMain.pCurve = new QwtPlotCurve("data moving up");
    // 设置曲线颜色
    m_tPlotMain.pCurve->setPen(QPen(Qt::yellow));
    // 抗锯齿设置
    m_tPlotMain.pCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true );
    // 设置曲线插值
//    m_pPlotCurveChannel1->setCurveAttribute(QwtPlotCurve::Fitted,true);
    // 关联曲线
    m_tPlotMain.pCurve->attach( m_tPlotMain.pPlot );

    // 通道1曲线初始化
    m_tPlotModu.pCurve = new QwtPlotCurve("data moving down");
    // 设置曲线颜色
    m_tPlotModu.pCurve->setPen(QPen(Qt::white));
    // 抗锯齿设置
    m_tPlotModu.pCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true );
    // 设置曲线插值
    m_tPlotModu.pCurve->setCurveAttribute(QwtPlotCurve::Fitted,true);
    // 关联曲线
    m_tPlotModu.pCurve->attach( m_tPlotModu.pPlot );


    TWaveFormParamBase tWaveSin( 0.5 , 90.0 , 100 , 1.0 );
    drawFunctionSin( m_tPlotMain , tWaveSin , 2 );
    drawFunctionSin( m_tPlotModu , tWaveSin , 2 );

    TWaveFormParamBase tWaveCarr( 2.0 , 0 , 100 , 0.0 );
    drawFunctionModuAM(m_tPlotModu ,
                       tWaveSin , 2 ,
                       tWaveCarr , 10 );

    QStringList strListFunctions;
    strListFunctions<< "SIN"  << "AM" << "FM"<< "PulseM" << "ASK" << "FSK" << "PSK" << "QAM" ;
    ui->comboBox->addItems( strListFunctions );
}

PlotTestDlg::~PlotTestDlg()
{
    delete ui;
}

void PlotTestDlg::drawFunctionSin(const TPlotItem &tPlotItem , const TWaveFormParamBase &tWaveParam , int nDrawPeriodCount )
{
    double dMaxX = nDrawPeriodCount;

    double dAmp = tWaveParam.Vpp/2.0;

    tPlotItem.pPlot->setAxisScale( QwtPlot::xBottom, 0, dMaxX  );
    tPlotItem.pPlot->setAxisScale( QwtPlot::yLeft, tWaveParam.Offset-dAmp, tWaveParam.Offset+dAmp );

    tPlotItem.pMark->setValue( dMaxX / 2.0, tWaveParam.Offset );


    double dOffsetX = (dMaxX/PT_NUM);
    double p_cof = tWaveParam.Phase*M_PI/180.0;
    for ( int i = 0 ; i < PT_NUM ; i++  )
    {
        tPlotItem.x[i] = double(i)*dOffsetX;
        double d = (dAmp)*sin(2*M_PI*tPlotItem.x[i] + p_cof) + tWaveParam.Offset;// cos(2.0*M_PI*1.0/(1.0e-9*m_pdzSampCoordX[i]) );
        tPlotItem.y[i] = d;
    }

    tPlotItem.pScaleDraw->setCoef( tWaveParam.Period );

    // 设置采样数据
    tPlotItem.pCurve->setSamples( tPlotItem.x , tPlotItem.y , PT_NUM );

    // 重绘制
    tPlotItem.pPlot->replot();
//    tPlotItem.pPlot->axisWidget(QwtPlot::xBottom)->update();
}

void PlotTestDlg::drawFunctionPulse(const TPlotItem &tPlotItem , const TWaveFormParamPulse &tWaveParam , int nDrawPeriodCount)
{
    double dMaxX = nDrawPeriodCount;

    double dAmp = tWaveParam.Vpp/2.0;

    double dDuty = tWaveParam.width/tWaveParam.Period;

    tPlotItem.pPlot->setAxisScale( QwtPlot::xBottom, 0, dMaxX  );
    tPlotItem.pPlot->setAxisScale( QwtPlot::yLeft, tWaveParam.Offset-dAmp, tWaveParam.Offset+dAmp );


    tPlotItem.pMark->setValue( dMaxX / 2.0, tWaveParam.Offset );

    double dOffsetX = (dMaxX/PT_NUM);

    double L = tWaveParam.leading/tWaveParam.Period;
    double D = L + (tWaveParam.width-(tWaveParam.leading/2.0+tWaveParam.trailing/2.0))/tWaveParam.Period;
    double T = D + tWaveParam.trailing/tWaveParam.Period;
    double LCoef = tWaveParam.Vpp/(tWaveParam.leading/tWaveParam.Period);
    double TCoef = tWaveParam.Vpp/(tWaveParam.trailing/tWaveParam.Period);

    for ( int i = 0 ; i < PT_NUM ; i++  )
    {
        tPlotItem.x[i] = double(i)*dOffsetX;
        double x = tPlotItem.x[i] - ((int)tPlotItem.x[i])*1.0;
        if ( x == 0 )
        {
            tPlotItem.y[i] = -1*dAmp + tWaveParam.Offset;
        }
        else if ( x > 0 && x <= L )
        {
            tPlotItem.y[i] = -1.0*dAmp + x*LCoef+ tWaveParam.Offset;
        }
        else if ( x > L && x <= D )
        {
            tPlotItem.y[i] = dAmp + tWaveParam.Offset;
        }
        else if ( x > D && x <= T )
        {
            tPlotItem.y[i] = -1.0*dAmp + (T-x)*TCoef+ tWaveParam.Offset;
        }
        else if ( x > T && x < 1.0 )
        {
            tPlotItem.y[i] = -1.0*dAmp + tWaveParam.Offset;
        }
        else
        {

        }

    }

    tPlotItem.pScaleDraw->setCoef( tWaveParam.Period );

    // 设置采样数据
    tPlotItem.pCurve->setSamples( tPlotItem.x , tPlotItem.y , PT_NUM );

    // 重绘制
    tPlotItem.pPlot->replot();
    tPlotItem.pPlot->update();
}

void PlotTestDlg::drawFunctionModuAM(const TPlotItem &tPlotItem ,
                                     const TWaveFormParamBase &tWaveParamModuSig , int nDrawPeriodModuSigCount,
                                     const TWaveFormParamBase &tWaveParamCarrierSig , int nDrawPeriodCarrierSigCount)
{
    double dMainF = nDrawPeriodCarrierSigCount;
    double Vpp = tWaveParamCarrierSig.Vpp;

    double dAmp = Vpp/2.0;

    m_tPlotMain.pPlot->setAxisScale( QwtPlot::xBottom, 0, dMainF  );
    m_tPlotMain.pPlot->setAxisScale( QwtPlot::yLeft, -dAmp*2.5, dAmp*2.5 );

    m_tPlotMain.pMark->setValue( dMainF / 2.0, 0.0 );


    double dPhaseCof = M_PI/180.0;
    double dOffsetMain = dMainF/PT_NUM;
    double dOffsetModu = (double)nDrawPeriodModuSigCount/(double)PT_NUM;
    for ( int i = 0 ; i < PT_NUM ; i++  )
    {
        m_tPlotMain.x[i] = double(i)*dOffsetMain;
        double dAmpSin = (tWaveParamModuSig.Vpp/2.0)*sin(2*M_PI* double(i)*dOffsetModu + dPhaseCof*tWaveParamModuSig.Phase ) + tWaveParamModuSig.Offset;
        m_tPlotMain.y[i] = (dAmp+dAmpSin)*sin(2*M_PI*m_tPlotMain.x[i] + dPhaseCof*tWaveParamCarrierSig.Phase) + tWaveParamCarrierSig.Offset;
    }

    // 设置采样数据
    m_tPlotMain.pCurve->setSamples( m_tPlotMain.x , m_tPlotMain.y , PT_NUM );

    // 重绘制
    m_tPlotMain.pPlot->replot();
}

void PlotTestDlg::drawFunctionModuFM(const TPlotItem &tPlotItem,
                                     const TWaveFormParamBase &tWaveParamModuSig, int nDrawPeriodModuSigCount,
                                     const TWaveFormParamBase &tWaveParamCarrierSig, int nDrawPeriodCarrierSigCount,
                                     double dDCoef )
{
    double D = dDCoef; // 调制系数
    double dMainF = nDrawPeriodCarrierSigCount;
    double Vpp = tWaveParamCarrierSig.Vpp;

    double dAmp = Vpp/2.0;

    tPlotItem.pPlot->setAxisScale( QwtPlot::xBottom, 0, dMainF  );
    tPlotItem.pPlot->setAxisScale( QwtPlot::yLeft, -dAmp, dAmp );

    tPlotItem.pMark->setValue( dMainF / 2.0, 0.0 );


    double dPhaseCof = M_PI/180.0;
    double dOffsetMain = dMainF/PT_NUM;
    double dOffsetModu = (double)nDrawPeriodModuSigCount/(double)PT_NUM;
    for ( int i = 0 ; i < PT_NUM ; i++  )
    {
        tPlotItem.x[i] = double(i)*dOffsetMain;
        double dModuX = double(i)*dOffsetModu;
//      double dAmpSin = (tWaveParamModuSig.Vpp/2.0)*sin(2*M_PI* double(i)*dOffsetModu - dPhaseCof*tWaveParamModuSig.Phase ) + tWaveParamModuSig.Offset;
        tPlotItem.y[i] = (dAmp)*cos(2*M_PI*m_tPlotMain.x[i])*cos(D*sin(2*M_PI*dModuX)) - dAmp*sin(2*M_PI*m_tPlotMain.x[i])*sin(D*sin(2*M_PI*dModuX));
    }

    // 设置采样数据
    tPlotItem.pCurve->setSamples( m_tPlotMain.x , m_tPlotMain.y , PT_NUM );

    // 重绘制
    tPlotItem.pPlot->replot();
}

void PlotTestDlg::getParamBase(TWaveFormParamBase &tWaveParamModuSig)
{
    double dFreq = ui->dsMainFreq->value();
    double dAmpl = ui->dsMainAmpl->value();
    double dPhase = ui->dsMainPhase->value();
    double dOffset = ui->dsMainOffset->value();
    TWaveFormParamBase tBase( dAmpl*2 , dPhase,  1.0/dFreq , dOffset );
    tWaveParamModuSig = tBase;
}

void PlotTestDlg::getParamAModu(TWaveFormParamBase &tWaveParamModuSig)
{
    double dFreq = ui->dsAModuFreq->value();
    double dAmpl = ui->dsAModuDeep->value();
    double dPhase = ui->dsAModuPhase->value();
    double dOffset = ui->dsAModuOffset->value();
    TWaveFormParamBase tBase( dAmpl*2 , dPhase,  1.0/dFreq , dOffset );
    tWaveParamModuSig = tBase;
}

void PlotTestDlg::on_comboBox_currentIndexChanged(int index)
{
    switch ( index )
    {
    case 0: // sin
    {
        TWaveFormParamBase tBase;
        getParamBase( tBase );
        drawFunctionSin( m_tPlotMain , tBase , 2 );
        drawFunctionSin( m_tPlotModu , tBase , 2 );
        break;
    }
    case 1: // am
    {
        TWaveFormParamBase tMain;
        getParamBase( tMain );
        TWaveFormParamBase tAModu;
        getParamAModu( tAModu );
        drawFunctionSin( m_tPlotModu , tAModu , 2 );
        double dFreqCountCoef = (1.0/tMain.Period)/(1.0/tAModu.Period);
        drawFunctionModuAM( m_tPlotMain ,
                            tAModu , 2 ,
                            tMain , 2*dFreqCountCoef );
        break;
    }
    case 2: // fm
    {
        TWaveFormParamBase tMain;
        getParamBase( tMain );
        TWaveFormParamBase tAModu;
        getParamAModu( tAModu );
        drawFunctionSin( m_tPlotModu , tAModu , 2 );
        double dFreqCountCoef = (1.0/tMain.Period)/(1.0/tAModu.Period);
        double dFMDCoef = ui->dsAModuFMDcoef->value();
        drawFunctionModuFM( m_tPlotMain ,
                            tAModu , 2 ,
                            tMain , 2*dFreqCountCoef , dFMDCoef );
        break;
    }
    default:
        break;
    }
}



void PlotTestDlg::paramChanged(double)
{
    on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());
}
