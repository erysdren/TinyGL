
/* headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#include <GL/gl.h>
#include <GL/ostinygl.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thirdparty/stb_image_write.h"

#include "ui.h"

#define RGB565_RED(c) ((uint8_t)((((c) & 0xF800) >> 11) << 3))
#define RGB565_GRN(c) ((uint8_t)((((c) & 0x7E0) >> 5) << 2))
#define RGB565_BLU(c) ((uint8_t)(((c) & 0x1F) << 3))

/* globals */
ostgl_context_t *ctx;

int error(const char *s, ...)
{
	va_list ap;

	va_start(ap, s);
	vfprintf(stdout, s, ap);
	fprintf(stdout, "\n");
	va_end(ap);

	return 1;
}

/* open window, handle inputs */
int ui_loop(int argc, char **argv, const char *name)
{
	/* variables */
	int w, h;
	char filename[64];
	uint8_t *pixels;
	int i;

	/* get width, height from commandline */
	if (argc >= 3)
	{
		if (!(w = atoi(argv[1]))) return error("error: must provide width value greater than 0");
		if (!(h = atoi(argv[2]))) return error("error: must provide height value greater than 0");
	}
	else
	{
		return error("usage: %s <width> <height>", argv[0]);
	}

	/* alloc */
	ctx = ostgl_create_context(w, h, 16);
	ostgl_make_current(ctx);
	pixels = malloc(w * h * 3);

	/* call user functions */
	init();
	reshape(ctx->width, ctx->height);

	/* run a frame */
	idle();

	/* convert buffer */
	for (i = 0; i < w * h; i++)
	{
		pixels[i * 3] = RGB565_RED(((uint16_t *)ctx->pixels)[i]);
		pixels[(i * 3) + 1] = RGB565_GRN(((uint16_t *)ctx->pixels)[i]);
		pixels[(i * 3) + 2] = RGB565_BLU(((uint16_t *)ctx->pixels)[i]);
	}

	/* save frame */
	snprintf(filename, 64, "%s.png", name);
	stbi_write_png(filename, w, h, 3, pixels, w * 3);
	printf("saved %s\n", filename);

	/* shutdown */
	ostgl_delete_context(ctx);
	free(pixels);

	/* return success */
	return 0;
}

/* swap buffers */
void swap_buffers(void)
{
	return;
}
