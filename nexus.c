#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

char *nexus_version_string = "0.0.2";

SDL_DisplayMode display_mode;
SDL_Window *window;
SDL_GLContext context;
GLfloat winX = 100.0, winY = 40.0, winW = 800.0, winH = 600.0;
char window_title[1024];
SDL_Event event;

void NexusExit(void) {
	printf("\nnexus exited\n");
}

int main(int argc, char **argv) {
	printf("nexus %s started\n", nexus_version_string);

	atexit(NexusExit);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf ("nexus: SDL_Init() failed.\n");
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
//    if (verbose) {
        int major, minor;
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
        printf("SDL OpenGL %d.%d\n", major, minor);
//    }

	sprintf(window_title, "nexus %s", nexus_version_string);
    window = SDL_CreateWindow(window_title, winX, winY + 30, winW, winH,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        //SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_WarpMouseInWindow(window, winW / 2, winH / 2);

    context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        printf("nexus: Cannot create SDL2/GL context. Error: %s\n",
			SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf ("nexus: Cannot initialize GLEW.\n");
        SDL_GL_DeleteContext(context);
        SDL_Quit();
        exit(1);
    }

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport((GLint)0, (GLint)0, (GLsizei)winW, (GLsizei)winH);

	GLfloat delta = 0.0;
	int mainloopend = 0;
	int fps = 0;
	time_t t0, tprev = 0;
	while (!mainloopend) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, winW, winH, 0.0, 0.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0, 1.0, 10.0,
				0.0, 1.0, 0.0,
				0.0, 1.0, 0.0);

		glTranslatef(winW/2, winH/2, 0.0);
		glRotatef(delta, 0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		glColor3f(0.6, 0.7, 0.8);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0.0);
		glVertex3f(10.0, 10.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();

		++fps;
		SDL_GL_SwapWindow(window);
		t0 = time(NULL);
		if (t0 - tprev > 0) {
			tprev = t0;
			printf("\r%d fps", fps);
			fflush(stdout);
			fps = 0;
		}

		delta += 1.0;
		if (delta >= 360.0)
			delta -= 360.0;

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				mainloopend = 1;
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_q:
					mainloopend = 1;
					break;
				default:
					break;
				}
			}
		}
	}

	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

