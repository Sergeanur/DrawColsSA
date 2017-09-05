#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fstream>

extern bool gbShowCollision;

#define _x(a) RsGlobal->MaximumWidth - (1.0 / 640.0) * RsGlobal->MaximumWidth * a
#define _y(a) RsGlobal->MaximumHeight * (1.0 / 448.0) * a
#define _width(a) RsGlobal->MaximumWidth * (1.0 / 640.0) * a 
#define _height(a) RsGlobal->MaximumHeight * (1.0 / 448.0) * a
