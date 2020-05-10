#ifndef XVIDEOWIDGET_H
#define XVIDEOWIDGET_H

#include <QOpenGLWidget>
#include <QImage>
#include <opencv2/opencv.hpp>

class XVideoWidget : public QOpenGLWidget
{
    Q_OBJECT

    QImage img;

    void paintEvent(QPaintEvent* e);

public:
    XVideoWidget(QWidget* parent = 0);

    void setIsChanged(bool isChanged);

public slots:

    void setImage(cv::Mat mat);
};

#endif // XVIDEOWIDGET_H
