#ifndef PROCESSINGCONTROLLER_H
#define PROCESSINGCONTROLLER_H

#include <QObject>
#include <QString>

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
    void loadAois(QString aoiFile);
    void clearAois();

signals:
    void statusChange(bool, int, double);
    void nextCapture();

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
