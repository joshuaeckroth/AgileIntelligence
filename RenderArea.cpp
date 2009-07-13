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

  cameraViews = new CameraView*[numCameras];

  QGridLayout *layout = new QGridLayout;
  int camera = 0;
  for(int x = 0; x < gridX; ++x)
  {
      for(int y = 0; y < gridY; ++y)
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
