#include "CaptureThread.h"
#include "Camera.h"

CaptureThread::CaptureThread(int _numCameras, Camera** _cameras, double _fps)
        : QThread(), numCameras(_numCameras), cameras(_cameras), fps(_fps),
        frameNumber(0)
{
}

void CaptureThread::run()
{
    double frameTime;
    QImage** frames = new QImage*[numCameras];
    while(true)
    {
        if(!captureActive)
        {
            captureLock.lock();
            captureWait.wait(&captureLock);
            captureLock.unlock();
        }

        if(!doNextCapture)
        {
            doNextCaptureLock.lock();
            doNextCaptureWait.wait(&doNextCaptureLock);
            doNextCaptureLock.unlock();
        }

        for(int camera = 0; camera < numCameras; ++camera)
        {
            cameras[camera]->grabFrame();
        }

        for(int camera = 0; camera < numCameras; ++camera)
        {
            frames[camera] = cameras[camera]->retrieveFrame();
        }

        frameNumber++;
        frameTime = frameNumber / fps;

        doNextCapture = false;

        emit newFrames(frames, frameNumber, frameTime);
    }
}

void CaptureThread::nextCapture()
{
    doNextCapture = true;
    doNextCaptureWait.wakeAll();
}

bool CaptureThread::startCapture()
{
    if(!captureActive)
    {
        nextCapture();
        captureActive = true;
        captureWait.wakeAll();
        return true;
    }
    return false;
}

void CaptureThread::stopCapture()
{
    captureActive = false;
}
