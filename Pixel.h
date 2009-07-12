/*
 * Pixel.h
 *
 *  Created on: Jul 12, 2009
 *      Author: josh
 */

#ifndef PIXEL_H_
#define PIXEL_H_

class Pixel
{
public:
	Pixel(int _x, int _y);
	void setValid(bool _valid);

	bool isValid() { return valid; }
	int getX() { return x; }
	int getY() { return y; }

private:
	bool valid;
	int x;
	int y;
};

#endif /* PIXEL_H_ */
