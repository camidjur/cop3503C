#pragma once
#include "Pixels.h"
#include <vector>

class Header
{
public:
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;
	vector <Pixels> pixels;

	Header();
};

