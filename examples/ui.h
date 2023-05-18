
/* program-defined */
void draw();
void idle();
GLenum key(int k, GLenum mask);
void reshape(int width, int height);
void init();

/* open window, swap buffer */
int ui_loop(int argc, char **argv, const char *name);
void swap_buffers();

#define KEY_UP 0xe000
#define KEY_DOWN 0xe001
#define KEY_LEFT 0xe002
#define KEY_RIGHT 0xe003
#define KEY_ESCAPE 0xe004
