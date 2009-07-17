#ifndef AREAOFINTERESTREADER_H
#define AREAOFINTERESTREADER_H

#include <vector>
#include <QString>
#include "AreaOfInterest.h"

class AreaOfInterestReader
{
public:
    static std::vector<AreaOfInterest> loadAois(QString aoiFile);
};

#endif // AREAOFINTERESTREADER_H
