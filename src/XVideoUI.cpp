#pragma execution_character_set("utf-8")

#include "XVideoUI.h"
#include "XVideoThread.h"
#include "ui_XVideoUI.h"

#include <QFileDialog>
#include <string>
#include <QMessageBox>
#include <QDesktopWidget>

XVideoUI::XVideoUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XVideoUI)
{
    ui->setupUi(this);
    ui->controlButton->setFont(QFont("等线",30));
    setWindowFlag(Qt::FramelessWindowHint);

    qRegisterMetaType<cv::Mat>("cv::Mat");

    connect(XVideoThread::get(),SIGNAL(viewImage1(cv::Mat)),ui->src1Video,SLOT(setImage(cv::Mat)));

    startTimer(40);
}

XVideoUI::~XVideoUI()
{
    delete ui;
}

void XVideoUI::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragPos = QCursor::pos() - frameGeometry().topLeft();
    }
    QWidget::mousePressEvent(event);
}

void XVideoUI::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QRect desktopRc = QApplication::desktop()->availableGeometry();
        QPoint curPoint = event->globalPos() - m_dragPos;

        if (event->globalY() > desktopRc.height())
        {
            curPoint.setY(desktopRc.height() - m_dragPos.y());
        }
        move(curPoint);
    }
    QWidget::mouseMoveEvent(event);
}

void XVideoUI::timerEvent(QTimerEvent*)
{
    if(sliderPressed)
    {
        return;
    }

    double pos = XVideoThread::get()->getPos();
    ui->playSlider->setValue(pos * 1000);
}

void XVideoUI::on_openButton_clicked()
{
    QString name = QFileDialog::getOpenFileName(this,QString("请选择视频文件"));

    if(!name.isEmpty())
    {
        string file = name.toLocal8Bit().data();

        if(XVideoThread::get()->open(file))
        {
            setControlButtonText(ON);
        }
        else
        {
            setControlButtonText(OFF);
            QMessageBox::critical(this,"",name + "open failed!");
        }
    }
}

void XVideoUI::setControlButtonText(Status status)
{
    switch (status)
    {
        case ON:
            ui->controlButton->setText("■");
            ui->controlButton->setFont(QFont("等线",15));
            break;

        case OFF:
            ui->controlButton->setText("▶");
            ui->controlButton->setFont(QFont("等线",30));
            break;

        default:
            break;
    }
}

void XVideoUI::on_playSlider_sliderPressed()
{
    sliderPressed = true;
}

void XVideoUI::on_playSlider_sliderMoved(int position)
{
    sliderPressed = false;
    XVideoThread::get()->seek((double)position / 1000.);
}

void XVideoUI::on_controlButton_clicked()
{
    XVideoThread* video = XVideoThread::get();
    bool isStart = video->getStart();
    video->setStart(!isStart);

    if(!isStart)
    {
        setControlButtonText(ON);
    }
    else
    {
        setControlButtonText(OFF);
    }
}
