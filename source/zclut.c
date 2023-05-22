/* 
 * zclut: use predefined 8bpp palette for zbuffer
 * by erysdren (it/she)
 */

#include <stdlib.h>
#include <stdio.h>
#include "zbuffer.h"
#include <assert.h>

#if defined(TGL_FEATURE_8_BITS)

#if TGL_FEATURE_RENDER_BITS != 16
#error TGL_FEATURE_8_BITS is not supported for this value of TGL_FEATURE_RENDER_BITS
#endif

#define ISQR(x) ((x) * (x))
#define _R(c) ((c) & 0xF800)
#define _G(c) ((c) & 0x7E0)
#define _B(c) ((c) & 0x1F)

#define RGB565_RED8(c) ((uint8_t)((((c) & 0xF800) >> 11) << 3))
#define RGB565_GRN8(c) ((uint8_t)((((c) & 0x7E0) >> 5) << 2))
#define RGB565_BLU8(c) ((uint8_t)(((c) & 0x1F) << 3))

/* find nearest color index in palette */
static uint8_t ZB_paletteSearch(ZBuffer *zb, ZBufferRGB color)
{
	int i, dist = INT32_MAX;
	uint8_t pen;

	for (i = 256; i--;)
	{
		int rank =
			ISQR(zb->palette->colors[i].r - color.r) +
			ISQR(zb->palette->colors[i].g - color.g) +
			ISQR(zb->palette->colors[i].b - color.b);

		if (rank < dist)
		{
			pen = i;
			dist = rank;
		}
	}

	return pen;
}

/* assumes 256 colors */
void ZB_generateCLUT(ZBuffer *zb, ZBufferRGB *colors)
{
	/* variables */
	int i, r, g, b;

	/* allocate palette */
	zb->palette = gl_zalloc(sizeof(ZBufferPalette));

	/* import palette colors */
	for (i = 0; i < 256; i++)
		zb->palette->colors[i] = colors[i];

	/* generate lookup table */
	for (r = 0; r < 32; r++)
	{
		for (g = 0; g < 64; g++)
		{
			for (b = 0; b < 32; b++)
			{
				ZBufferRGB color;

				color.r = r * 8;
				color.g = g * 4;
				color.b = b * 8;

				zb->palette->clut[r][g][b] = ZB_paletteSearch(zb, color);
			}
		}
	}

	/* set flag */
	zb->use_palette = 1;
}

/* dither frame buffer to predefined palette */
void ZB_ditherFrameBufferPalette(ZBuffer *zb, uint8_t *buf, int stride)
{
	int i;

	for (i = 0; i < zb->xsize * zb->ysize; i++)
	{
		int r, g, b;

		r = RGB565_RED8(zb->pbuf[i]) / 32;
		g = RGB565_BLU8(zb->pbuf[i]) / 64;
		b = RGB565_GRN8(zb->pbuf[i]) / 32;

		buf[i] = zb->palette->clut[r][g][b];
	}
}

#endif /* TGL_FEATURE_8_BITS */
