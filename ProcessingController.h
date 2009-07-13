#ifndef PROCESSINGCONTROLLER_H
#define PROCESSINGCONTROLLER_H

#include <QObject>

class RenderArea;
class CaptureThread;
class Camera;
class QImage;

class ProcessingController : public QObject
{
    Q_OBJECT
public:
    ProcessingController(RenderArea* _renderArea, int _numCameras);
    ~ProcessingController();

signals:
    void statusChange(bool, int, double);

public slots:
    void startProcessing();
    void stopProcessing();

private slots:
    void processNewFrames(QImage**, int, double);

private:
    RenderArea* renderArea;
    int numCameras;
    Camera** cameras;
    CaptureThread* captureThread;
};

#endif // PROCESSINGCONTROLLER_H
