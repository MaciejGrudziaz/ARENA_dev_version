#pragma once
#include "Vector.h"

bool CheckPointInTriangle(Vector point, Vector triangle[], Vector normal);												//sprawdzenie czy pkt. 'point' znajduje si� wewn�trz tr�jk�ta 'triangle'

Vector PointSurfaceProjection(Vector surface[], Vector normal, Vector point, Vector projectionVec);						//rzut pkt. 'point' na powierzchni� 'surface' wzd�u� wek. 'projectionVec'