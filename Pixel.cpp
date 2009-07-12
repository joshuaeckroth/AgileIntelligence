/*
 * Pixel.cpp
 *
 *  Created on: Jul 12, 2009
 *      Author: josh
 */

#include "Pixel.h"

Pixel::Pixel(int _x, int _y)
	: valid(true), x(_x), y(_y)
{}

void Pixel::setValid(bool _valid)
{
	valid = _valid;
}
