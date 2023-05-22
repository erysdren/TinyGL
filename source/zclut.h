/* 
 * zbuffer: use predefined 8bpp palette
 * by erysdren (it/she)
 */

#include <stdint.h>

/* palette entry */
typedef struct
{
	uint8_t r, g, b; /* color values */
} ZBufferRGB;

/* palette */
typedef struct
{
	ZBufferRGB colors[256]; /* palette colors */
	uint8_t clut[32][64][32]; /* color lookup table (RGB565 only) */
} ZBufferPalette;
