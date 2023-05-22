
/* guard */
#ifndef _tgl_osbuffer_h_
#define _tgl_osbuffer_h_
#ifdef __cplusplus
extern "C" {
#endif

/* struct type */
typedef struct
{
	void *zb;
	void *pixels;
	void *palette;
	int width, height;
	int depth;
} ostgl_context;

/* functions */

/* create context. valid bits per pixel are 8, 16, 24, and 32. */
ostgl_context *ostgl_create_context(int width, int height, int depth);

/* if you have multiple contexts, call this to make one "current" */
void ostgl_make_current(ostgl_context *context);

/* delete context and free all associated memory */
void ostgl_delete_context(ostgl_context *context);

/* resize framebuffer to specified with and height */
void ostgl_resize(ostgl_context *context, int width, int height);

/* convert framebuffer to specified bpp */
/* you only need to call this function if your target bits-per-pixel != 16. */
void *ostgl_convert_framebuffer(ostgl_context *context);

/* guard */
#ifdef __cplusplus
}
#endif
#endif /* _tgl_osbuffer_h_ */
