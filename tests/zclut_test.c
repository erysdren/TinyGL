/* 
 * zbuffer: use predefined 8bpp palette
 * by erysdren (it/she)
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "../source/zbuffer.h"
#include "../source/thirdparty/quake_palette.h"
#include "gears.h"

#define WIDTH 640
#define HEIGHT 480
#define ARGB(r, g, b, a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))
#define RGBA(r, g, b, a) (((r) << 24) | ((g) << 16) | ((b) << 8) | (a))

int main(int argc, char **argv)
{
	/* variables */
	ZBuffer *zb;
	uint8_t *pixels;
	FILE *file;
	int i;

	/* init output pixels */
	pixels = (uint8_t *)malloc(WIDTH * HEIGHT);

	/* open zb */
	zb = ZB_open(WIDTH, HEIGHT, ZB_MODE_INDEX, 0, NULL, NULL, NULL);
	glInit((void *)zb);

	/* gears */
	gears_init();
	gears_reshape(WIDTH, HEIGHT);
	gears_idle();

	/* copy */
	ZB_copyFrameBuffer(zb, pixels, WIDTH * sizeof(uint8_t));

	/* save */
	file = fopen("zclut_test.data", "wb");
	fwrite(pixels, sizeof(uint8_t), WIDTH * HEIGHT, file);
	fclose(file);

	/* close up */
	ZB_close(zb);
	glClose();
	free(pixels);

	/* return yes */
	return 0;
}
