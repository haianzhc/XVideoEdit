#ifndef XVIDEOUI_H
#define XVIDEOUI_H

#include <QWidget>
#include <QMouseEvent>
#include <QFont>

static bool sliderPressed = false;

using namespace std;

namespace Ui {
class XVideoUI;
}

class XVideoUI : public QWidget
{
    Q_OBJECT

    enum Status
    {
        ON,
        OFF
    };

    QPoint m_dragPos;

    void timerEvent(QTimerEvent* e);
    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);

public:

    XVideoUI(QWidget *parent = 0);
    ~XVideoUI();

    void setControlButtonText(Status status);

private slots:
    void on_openButton_clicked();

    void on_playSlider_sliderPressed();

    void on_playSlider_sliderMoved(int position);

    void on_controlButton_clicked();

private:
    Ui::XVideoUI *ui;
};

#endif // XVIDEOUI_H
