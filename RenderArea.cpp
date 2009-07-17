#include "RenderArea.h"
#include "CameraView.h"
#include <QGridLayout>

RenderArea::RenderArea(QWidget* parent,
                       int _numCameras,
                       int _gridX, int _gridY)
        : QWidget(parent), numCameras(_numCameras), gridX(_gridX), gridY(_gridY)
{
  setAttribute(Qt::WA_OpaquePaintEvent, true);
  setAttribute(Qt::WA_PaintOnScreen, true);
  setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,
                            QSizePolicy::MinimumExpanding));

  aois = new std::vector<QPolygon>[numCameras];

  cameraViews = new CameraView*[numCameras];

  QGridLayout *layout = new QGridLayout;
  int camera = 0;
  for(int y = 0; y < gridY; ++y)
  {
      for(int x = 0; x < gridX; ++x)
      {
          cameraViews[camera] = new CameraView(this, QString("Camera %1").arg(camera + 1));
          layout->addWidget(cameraViews[camera], y, x);
          camera++;
      }
  }
  setLayout(layout);
}

void RenderArea::renderFrame(int camera, QImage* frame)
{
    cameraViews[camera]->updateFrame(frame);
}

void RenderArea::addAreaOfInterest(int camera, QPolygon polygon)
{
    aois[camera].push_back(polygon);
    cameraViews[camera]->setAois(aois[camera]);
}

void RenderArea::clearAreasOfInterest()
{
    for(int camera = 0; camera < numCameras; ++camera)
    {
        aois[camera].clear();
        cameraViews[camera]->setAois(aois[camera]);
    }
}
