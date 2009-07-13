#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QWidget>
#include <QString>

class QImage;

class CameraView : public QWidget
{
public:
    CameraView(QWidget* parent, QString _id);
    void updateFrame(QImage* _frame);

protected:
    void paintEvent(QPaintEvent*);

private:
    QString id;
    QImage* frame;
};

#endif // CAMERAVIEW_H
