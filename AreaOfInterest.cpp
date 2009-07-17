#include "AreaOfInterest.h"

AreaOfInterest::AreaOfInterest()
{
}

void AreaOfInterest::addPoint(LatLon latlon)
{
    points.push_back(latlon);
}

int AreaOfInterest::numberOfPoints()
{
    return points.size();
}

LatLon AreaOfInterest::begin()
{
    it = points.begin();
    return *it;
}

bool AreaOfInterest::end()
{
    return it == points.end();
}

LatLon AreaOfInterest::next()
{
    return *(++it);
}
