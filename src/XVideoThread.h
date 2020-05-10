#ifndef XVIDEOTHREAD_H
#define XVIDEOTHREAD_H

#include <QThread>
#include <QMutex>
#include <opencv2/opencv.hpp>

class XVideoThread : public QThread
{
    Q_OBJECT

    int fps = 0;
    QMutex mutex;

    XVideoThread();
    ~XVideoThread();

    void run();

public:

    bool open(const std::string file);

    double getPos();

    bool seek(int frame);
    bool seek(double pos);

    void setStart(bool start);
    bool getStart();

    static XVideoThread* get();

signals:

    void viewImage1(cv::Mat mat);
};

#endif // XVIDEOTHREAD_H
