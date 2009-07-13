#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

class CameraView;
class QImage;

class RenderArea : public QWidget
{
public:
    RenderArea(QWidget* parent, int _numCameras,
               int _gridX, int _gridY);
    void renderFrame(int camera, QImage* frame);

private:
    int numCameras;
    int gridX;
    int gridY;
    CameraView** cameraViews;
};

#endif // RENDERAREA_H
