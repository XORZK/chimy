#include <assert.h>
#include <stdlib.h>
#include "vec.h"
#include "camera.h"

cam* create_camera(double fov, double ratio, double n, double f) {
	double scale = tan(fov * 0.5 * M_PI / 180) * n;

	cam* c = (cam*) malloc(sizeof(cam));

	c->px = c->py = c->pz = 0.0;
	c->fov = fov;
	c->ratio = ratio;
	c->n = n;
	c->f = f;
	c->t = scale;
	c->b = -c->t;
	c->r = ratio * scale;
	c->l = -c->r;

	return c;
}

// mat:
// | 2n/(r-l)	0	 (r+l)/(r-l)  0 |
// | 0      2n/(t-b) (t+b)/(t-b)  0 |
// | 0 0    -(f+n)/(f-n) -2fn/(f-n) |
// | 0          0        -1       0 |
v4 project(v3 p, cam *c) {
	v4 pp;

	pp.x1 = (2*c->n/(c->r-c->l))*p.x + ((c->r+c->l)/(c->r-c->l))*p.z;
	pp.x2 = (2*c->n/(c->t-c->b))*p.y + ((c->t+c->b)/(c->t-c->b))*p.z;
	pp.x3 = (-1*(c->f+c->n)/(c->f-c->n))*p.z + (-2*(c->f)*(c->n)/(c->f-c->n));
	pp.x4 = -p.z;

	return pp;
}

v3 get_ndc_coord(v4 p) {
	assert(p.x4 != 0);

	v3 pp = { p.x1, p.x2, p.x3 };

	if (p.x4 != 1) {
		pp.x = p.x1 / p.x4;
		pp.y = p.x2 / p.x4;
		pp.z = p.x3 / p.x4;
	}

	return pp;
}

void destroy_camera(cam *c) {
	if (c)
		free(c);
}
