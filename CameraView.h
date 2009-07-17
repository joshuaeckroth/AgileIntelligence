#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QWidget>
#include <QString>
#include <QPolygon>
#include <vector>

class QImage;

class CameraView : public QWidget
{
public:
    CameraView(QWidget* parent, QString _id);
    void updateFrame(QImage* _frame);
    void setAois(std::vector<QPolygon> _aois);

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);

private:
    QString id;
    QImage* frame;
    bool cameraIdsDrawn;
    std::vector<QPolygon> aois;
};

#endif // CAMERAVIEW_H
