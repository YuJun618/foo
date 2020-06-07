#include "plottestdlg.h"
#include "ui_plottestdlg.h"

#include "qwt_series_data.h"
#include "qwt_plot_canvas.h"
#include "qwt_painter.h"
#include "qwt_plot_grid.h"
#include "math.h"

#define PT_NUM 1000

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


    m_tPlotMain.pPlot->setTitle( "Plot test" );
    m_tPlotMain.pPlot->setCanvas( new Canvas );
    m_tPlotMain.pPlot->setAxisScale( QwtPlot::xBottom, 0, 2  );
    m_tPlotMain.pPlot->setAxisScale( QwtPlot::yLeft, -1, 1 );
    m_tPlotMain.pPlot->enableAxis( QwtPlot::xBottom , false );

 // ui->qwtPlot2->setTitle( "Plot test" );
    m_tPlotModu.pPlot->setCanvas( new Canvas );
 // ui->qwtPlot2->setAxisTitle( QwtPlot::xBottom, "Samp Point" );
    m_tPlotModu.pPlot->setAxisScale( QwtPlot::xBottom, 0, 2  );
    m_tPlotModu.pPlot->setAxisScale( QwtPlot::yLeft, -1, 1 );


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
    m_tPlotMain.pCurve->setRenderHint(QwtPlotItem::RenderAntialiased, false );
    // 设置曲线插值
//    m_pPlotCurveChannel1->setCurveAttribute(QwtPlotCurve::Fitted,true);
    // 关联曲线
    m_tPlotMain.pCurve->attach( m_tPlotMain.pPlot );

    // 通道1曲线初始化
    m_tPlotModu.pCurve = new QwtPlotCurve("data moving down");
    // 设置曲线颜色
    m_tPlotModu.pCurve->setPen(QPen(Qt::white));
    // 抗锯齿设置
    m_tPlotModu.pCurve->setRenderHint(QwtPlotItem::RenderAntialiased, false );
    // 设置曲线插值
//    m_pPlotCurveChannel1->setCurveAttribute(QwtPlotCurve::Fitted,true);
    // 关联曲线
    m_tPlotModu.pCurve->attach( m_tPlotModu.pPlot );


    drawFunctionSin( m_tPlotMain , 2.0 , 10 , 45.0 , 0 , 1.0 );
    drawFunctionSin( m_tPlotModu , 2.0 , 1 , 45.0 , 0 , 1.0 );

    drawFunctionModuAM();
}

PlotTestDlg::~PlotTestDlg()
{
    delete ui;
}

void PlotTestDlg::drawFunctionSin(const TPlotItem &tPlotItem  ,double Vpp , double f, double p, double t , double offset )
{
    double dMaxX = f;

    double dAmp = Vpp/2.0;

    tPlotItem.pPlot->setAxisScale( QwtPlot::xBottom, 0, dMaxX  );
    tPlotItem.pPlot->setAxisScale( QwtPlot::yLeft, offset-dAmp, offset+dAmp );

    tPlotItem.pMark->setValue( dMaxX / 2.0, offset );


    double dOffset = f/PT_NUM;
    double p_cof = p*M_PI/180.0;
    for ( int i = 0 ; i < PT_NUM ; i++  )
    {
        tPlotItem.x[i] = double(i)*dOffset;
        double d = (dAmp)*sin(2*M_PI*tPlotItem.x[i] + p_cof) + offset;// cos(2.0*M_PI*1.0/(1.0e-9*m_pdzSampCoordX[i]) );
        tPlotItem.y[i] = d;
    }

    // 设置采样数据
    tPlotItem.pCurve->setSamples( tPlotItem.x , tPlotItem.y , PT_NUM );

    // 重绘制
    tPlotItem.pPlot->replot();
}

void PlotTestDlg::drawFunctionPulse(const TPlotItem &tPlotItem ,double Vpp, double Freq, double Period, double Offset , double width, double leading, double trailing)
{
    double dMaxX = Freq;

    double dAmp = Vpp/2.0;

    double dDuty = width/Period;

    tPlotItem.pPlot->setAxisScale( QwtPlot::xBottom, 0, dMaxX  );
    tPlotItem.pPlot->setAxisScale( QwtPlot::yLeft, Offset-dAmp, Offset+dAmp );


    tPlotItem.pMark->setValue( dMaxX / 2.0, Offset );

    double dOffset = Freq/PT_NUM;

    double L = leading/Period;
    double D = L + (width-(leading/2.0+trailing/2.0))/Period;
    double T = D + trailing/Period;
    double LCoef = Vpp/(leading/Period);
    double TCoef = Vpp/(trailing/Period);

    for ( int i = 0 ; i < PT_NUM ; i++  )
    {
        tPlotItem.x[i] = double(i)*dOffset;
        double x = tPlotItem.x[i] - ((int)tPlotItem.x[i])*1.0;
        if ( x == 0 )
        {
            tPlotItem.y[i] = -1*dAmp + Offset;
        }
        else if ( x > 0 && x <= L )
        {
            tPlotItem.y[i] = -1.0*dAmp + x*LCoef+ Offset;
        }
        else if ( x > L && x <= D )
        {
            tPlotItem.y[i] = dAmp + Offset;
        }
        else if ( x > D && x <= T )
        {
            tPlotItem.y[i] = -1.0*dAmp + (T-x)*TCoef+ Offset;
        }
        else if ( x > T && x < 1.0 )
        {
            tPlotItem.y[i] = -1.0*dAmp + Offset;
        }
        else
        {

        }

    }

    // 设置采样数据
    tPlotItem.pCurve->setSamples( tPlotItem.x , tPlotItem.y , PT_NUM );

    // 重绘制
    tPlotItem.pPlot->replot();
}

void PlotTestDlg::drawFunctionModuAM()
{
    drawFunctionSin( m_tPlotModu , 1.0 , 2 , -90.0 , 0 , 0 );

    double dMainF = 10.0;
    double Vpp = 2.0;

    double dAmp = Vpp/2.0;

    m_tPlotMain.pPlot->setAxisScale( QwtPlot::xBottom, 0, dMainF  );
    m_tPlotMain.pPlot->setAxisScale( QwtPlot::yLeft, -dAmp*4, dAmp*4 );

    m_tPlotMain.pMark->setValue( dMainF / 2.0, 0.0 );


    double dOffsetMain = dMainF/PT_NUM;
    double dOffsetModu = 2.0/PT_NUM;
    for ( int i = 0 ; i < PT_NUM ; i++  )
    {
        m_tPlotMain.x[i] = double(i)*dOffsetMain;
        double dAmpSin = 0.5*sin(2*M_PI* double(i)*dOffsetModu - M_PI/2.0 ) + 1.0;
        m_tPlotMain.y[i] = (dAmpSin)*sin(2*M_PI*m_tPlotMain.x[i]);// cos(2.0*M_PI*1.0/(1.0e-9*m_pdzSampCoordX[i]) );
    }

    // 设置采样数据
    m_tPlotMain.pCurve->setSamples( m_tPlotMain.x , m_tPlotMain.y , PT_NUM );

    // 重绘制
    m_tPlotMain.pPlot->replot();
}

void PlotTestDlg::on_comboBox_currentIndexChanged(int index)
{
    switch ( index )
    {
    case 0:
        drawFunctionSin(  m_tPlotMain , 2.0 , 2 , 45.0 , 100 , 1.0 );
        drawFunctionSin( m_tPlotModu , 2.0 , 2 , 45.0 , 0 , 1.0 );
        break;
    case 1:
        drawFunctionPulse(  m_tPlotMain , 2.0 , 2 , 100 , 1.0 , 20 , 10 , 10 );
        drawFunctionPulse(  m_tPlotModu , 2.0 , 2 , 100 , 1.0 , 20 , 10 , 10 );
        break;
    default:
        break;
    }
}
