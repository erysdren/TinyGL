
#ifndef UI_H
#define UI_H
#ifdef __cplusplus
extern "C" {
#endif

/* program-defined */
void draw(void);
void idle(void);
GLenum key(int k);
void reshape(int width, int height);
void init(void);

/* open window, swap buffer */
int ui_loop(int argc, char **argv, const char *name);
void swap_buffers(void);

#define KEY_UP 0xe000
#define KEY_DOWN 0xe001
#define KEY_LEFT 0xe002
#define KEY_RIGHT 0xe003
#define KEY_ESCAPE 0xe004

#ifdef __cplusplus
}
#endif
#endif /* UI_H */
