#include "AreaOfInterestReader.h"
#include <gdal/ogrsf_frmts.h>

std::vector<AreaOfInterest> AreaOfInterestReader::loadAois(QString aoiFile)
{
    std::vector<AreaOfInterest> aois;

    OGRRegisterAll();
    OGRDataSource* ds = OGRSFDriverRegistrar::Open(aoiFile.toAscii(), FALSE);
    if(ds == NULL)
        return aois;

    OGRLayer* layer = ds->GetLayerByName("areas-of-interest");

    OGRFeature* feature;
    layer->ResetReading();
    while((feature = layer->GetNextFeature()) != NULL)
    {
        QString id(feature->GetFieldAsString(0));
        AreaOfInterest aoi;
        aoi.setId(id);

        OGRGeometry* geometry = feature->GetGeometryRef();
        if(geometry != NULL && wkbFlatten(geometry->getGeometryType()) == wkbPolygon)
        {
            OGRPolygon* polygon = (OGRPolygon*) geometry;
            OGRLinearRing* ring = polygon->getExteriorRing();
            int pointCount = ring->getNumPoints();
            for(int point = 0; point < pointCount; ++point)
            {
                double lat, lon;
                lon = ring->getX(point);
                lat = ring->getY(point);
                LatLon latlon(lat, lon);
                aoi.addPoint(latlon);
            }
        }
        aois.push_back(aoi);
    }

    return aois;
}
