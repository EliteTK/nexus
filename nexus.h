#ifndef NEXUS_H
#define NEXUS_H 1

#include <GL/gl.h>
#include <SDL2/SDL.h>

// nexus.c
extern char *nexus_version_string;
extern int mainloopend;
extern SDL_Window *window;
extern GLfloat winX, winY, winW, winH;
extern GLfloat flagX, flagY, flagZ;
extern GLfloat delta;
extern unsigned int fps;
extern char *fps_text;

void tvdiff(struct timeval *tv_start, struct timeval *tv_end, struct timeval *tv_diff);

// camera.c
struct Camera {
	GLfloat x, y, z,
		lx, ly, lz;
	GLfloat rotation_angle;
};
extern struct Camera cam;

void CameraRotateStep(GLfloat angle);

// event.c
#define MOD_NONE    0
#define MOD_CTRL    1
#define MOD_ALT     (1<<1)
#define MOD_SHIFT   (1<<2)
extern unsigned int mods;
extern unsigned int show_keys;
extern int mouse_x, mouse_y, mouse_x_prev, mouse_y_prev;

void EventCheck(void);

// flag.c
struct Flag {
	GLfloat x, y, z;
	unsigned int width, height, components;
	unsigned long value;
	GLuint texture_id;
	unsigned int texture_data_size;
	GLubyte *texture_data;
};
extern struct Flag flag01, flag02;

void FlagInit(void);
void FlagRender(void);
void FlagUpdate(void);

// font.c
void FontInit(void);
void FontRender(GLfloat x, GLfloat y, GLfloat z, char *text);
void FontRender2D(int x, int y, char *text);

// image.c
GLubyte *ImageFromFile_128(char *filename);
GLubyte *ImageFromFile_884x16(char *filename);
GLubyte *ImageFromFile_1024(char *filename);

// render.c
void Render(void);
extern void (*RenderFunc)(void);

// sky.c
extern GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4;

void SkyInit(void);
void SkyRender(void);

// state.c
#define STATE_MAIN      0
#define STATE_BROWSER   1
#define STATE_EDITOR    2
#define STATE_MEMORY    3
extern unsigned int state, state_prev;

unsigned int StateGet(void);
void StateSet(unsigned int newstate);

// terminal.c
#define TERMINAL_BUFFER_SIZE 4096
extern unsigned int terminal_visible;
extern char terminal_buffer[TERMINAL_BUFFER_SIZE];
extern unsigned int terminal_cursor_pos, terminal_cursor_blink;

void TerminalParse(void);
void TerminalRender(void);

////////////////////////////////
// Modules
////////////////////////////////

void BrowserRender(void);

void EditorRender(void);

void MemoryRender(void);

#endif /* NEXUS_H */
