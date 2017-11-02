#ifndef _RAYCASTER_H
#define _RAYCASTER_H

#define PIXEL_COUNT 1024

typedef struct Pixel {
	unsigned char r,g,b;
} Pixel;

typedef struct{
	V3 intersection;
	double t;
} RAY_OUTPUT;


#endif /*_RAYCASTER_H */
