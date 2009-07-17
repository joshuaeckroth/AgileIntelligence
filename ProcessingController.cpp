#include "ProcessingController.h"
#include "RenderArea.h"
#include "Camera.h"
#include "CaptureThread.h"
#include "AreaOfInterestReader.h"
#include "AreaOfInterest.h"
#include <vector>
#include <QDebug>

ProcessingController::ProcessingController(RenderArea* _renderArea,
                                           int _numCameras)
: renderArea(_renderArea), numCameras(_numCameras)
{
    cameras = new Camera*[numCameras];

    char* filename = (char*) malloc(150);
    char* homographyFile = (char*) malloc(100);
    char* inverseFile = (char*) malloc(100);
    for (int camera = 0; camera < numCameras; ++camera)
    {
        sprintf(filename, "/home/josh/research/datasets/peachtree-arterial/raw-video-0400pm-0415pm/peachtree-camera%d-0400pm-0415pm.avi", (camera+1));
        sprintf(homographyFile, "/home/josh/research/datasets/peachtree-arterial/peachtree-camera%d-homography.xml", (camera+1));
        sprintf(inverseFile, "/home/josh/research/datasets/peachtree-arterial/peachtree-camera%d-inverse.xml", (camera+1));

        cameras[camera] = new Camera(filename, homographyFile, inverseFile);
    }

    captureThread = new CaptureThread(numCameras, cameras, 10.0 /* fps */);
    connect(captureThread, SIGNAL(newFrames(QImage**, int, double)),
            this, SLOT(processNewFrames(QImage**, int, double)));
    connect(this, SIGNAL(nextCapture()), captureThread, SLOT(nextCapture()));
}

void ProcessingController::loadAois(QString aoiFile)
{
    std::vector<AreaOfInterest> aois = AreaOfInterestReader::loadAois(aoiFile);
    for(std::vector<AreaOfInterest>::iterator it = aois.begin(); it != aois.end(); ++it)
    {
        for(int camera = 0; camera < numCameras; camera++)
        {
            QPolygon translated = cameras[camera]->translateAreaOfInterest(*it);
            renderArea->addAreaOfInterest(camera, translated);
        }
    }
}

void ProcessingController::clearAois()
{
    renderArea->clearAreasOfInterest();
}

void ProcessingController::startProcessing()
{
    captureThread->startCapture();
    captureThread->start(QThread::IdlePriority);
}

void ProcessingController::stopProcessing()
{
    captureThread->stopCapture();
}

void ProcessingController::processNewFrames(QImage** frames,
                                            int frameNumber,
                                            double frameTime)
{
    for(int camera = 0; camera < numCameras; ++camera)
    {
        renderArea->renderFrame(camera, frames[camera]);
    }

    emit statusChange(captureThread->isCapturing(), frameNumber, frameTime);

    emit nextCapture();
}

ProcessingController::~ProcessingController()
{
    for (int i = 0; i < numCameras; i++)
    {
        delete cameras[i];
    }
}
