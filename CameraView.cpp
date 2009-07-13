#include "CameraView.h"
#include <QImage>
#include <QPainter>

CameraView::CameraView(QWidget* parent, QString _id)
        : QWidget(parent), id(_id), frame(NULL), cameraIdsDrawn(false)
{
}

void CameraView::updateFrame(QImage* _frame)
{
    if(frame != NULL)
    {
        delete frame->bits();
        delete frame;
    }
    frame = _frame;
    update();
}

void CameraView::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(!cameraIdsDrawn || frame == NULL)
    {
        painter.setBrush(Qt::black);
        painter.drawRect(rect());
        painter.setPen(Qt::blue);
        painter.drawText(QPoint(5, height() - 5), id);
        cameraIdsDrawn = true;
    }

    if(frame != NULL)
    {
        QImage scaledFrame = frame->scaledToWidth(width(), Qt::SmoothTransformation);
        int offsetY = (height() - scaledFrame.height()) / 2;
        painter.drawImage(QPoint(0,offsetY), scaledFrame);
    }

    painter.end();
}

void CameraView::resizeEvent(QResizeEvent*)
{
    cameraIdsDrawn = false;
}
