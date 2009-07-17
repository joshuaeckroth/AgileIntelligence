#ifndef AREAOFINTEREST_H
#define AREAOFINTEREST_H

#include <vector>
#include <QString>
#include "LatLon.h"

class AreaOfInterest
{
public:
    AreaOfInterest();
    void setId(QString _id) { id = _id; }
    QString getId() { return id; }
    void addPoint(LatLon latlon);
    int numberOfPoints();
    LatLon begin();
    bool end();
    LatLon next();

private:
    std::vector<LatLon> points;
    std::vector<LatLon>::iterator it;
    QString id;
};

#endif // AREAOFINTEREST_H
