/*
 * LatLon.h
 *
 *  Created on: Jul 12, 2009
 *      Author: josh
 */

#ifndef LATLON_H_
#define LATLON_H_

class LatLon
{
public:
	LatLon(double _lat, double _lon);

	double getLat() { return lat; }
	double getLon() { return lon; }

private:
	double lat;
	double lon;
};

#endif /* LATLON_H_ */
