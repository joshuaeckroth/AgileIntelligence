#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class Camera;
class QImage;

class CaptureThread : public QThread
{
    Q_OBJECT
public:
    CaptureThread(int _numCameras, Camera** _cameras, double _fps);
    void run();
    bool startCapture();
    void stopCapture();
    bool isCapturing() { return captureActive; }
    bool hasError() { return error; }

signals:
    void newFrames(QImage**, int, double);

public slots:
    void nextCapture();

private:
    QMutex captureLock;
    QWaitCondition captureWait;
    bool captureActive;
    QMutex doNextCaptureLock;
    QWaitCondition doNextCaptureWait;
    bool doNextCapture;
    int numCameras;
    Camera** cameras;
    double fps;
    int frameNumber;
    bool error;
};

#endif // CAPTURETHREAD_H
