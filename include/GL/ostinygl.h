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
	int width, height;
	int depth;
} ostgl_context;

/* functions */
ostgl_context *ostgl_create_context(int width, int height, int depth);
void ostgl_make_current(ostgl_context *context);
void ostgl_delete_context(ostgl_context *context);
void ostgl_resize(ostgl_context *context, int width, int height);

#ifdef __cplusplus
}
#endif

#endif /* _tgl_osbuffer_h_ */
