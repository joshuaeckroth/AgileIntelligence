#include "CameraView.h"
#include <QImage>
#include <QPainter>
#include <QDebug>

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

void CameraView::setAois(std::vector<QPolygon> _aois)
{
    aois = _aois;
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
        double scaleFactor = (double)scaledFrame.width() / (double)frame->width();
        int offsetY = (height() - scaledFrame.height()) / 2;
        painter.drawImage(QPoint(0,offsetY), scaledFrame);

        painter.setClipRect(0, offsetY, width(), scaledFrame.height());

        painter.setBrush(QBrush(QColor(200, 200, 200, 150)));
        for(std::vector<QPolygon>::iterator it = aois.begin(); it != aois.end(); ++it)
        {
            QPolygon scaledAoi;
            for(int i = 0; i < it->size(); ++i)
            {
                QPoint point = it->at(i);
                QPoint scaledPoint((int)((double)point.x() * scaleFactor),
                                   (int)((double)point.y() * scaleFactor) + offsetY);
                scaledAoi << scaledPoint;
            }
            painter.drawPolygon(scaledAoi);
        }
    }

    painter.end();
}

void CameraView::resizeEvent(QResizeEvent*)
{
    cameraIdsDrawn = false;
}
