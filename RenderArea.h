#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPolygon>
#include <vector>

class CameraView;
class QImage;

class RenderArea : public QWidget
{
public:
    RenderArea(QWidget* parent, int _numCameras,
               int _gridX, int _gridY);
    void renderFrame(int camera, QImage* frame);
    void addAreaOfInterest(int camera, QPolygon polygon);
    void clearAreasOfInterest();

private:
    int numCameras;
    int gridX;
    int gridY;
    CameraView** cameraViews;
    std::vector<QPolygon>* aois;
};

#endif // RENDERAREA_H
