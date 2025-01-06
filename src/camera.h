#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include <math.h>
#include "vec.h"

#define DEFAULT_CAMERA_FOV 90
#define DEFAULT_NEAR_DIST 0.1
#define DEFAULT_FAR_DIST 100

typedef struct cam {
	double px, py, pz;
	double fov, ratio;
	double n, f, b, t, l, r;
} cam;

cam* create_camera(double fov, double ratio, double n, double f);

v4 project(v3 p, cam *c);

v3 get_ndc_coord(v4 p);

void destroy_camera(cam *c);

#endif
