#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "nexus.h"

GLfloat memory_value;
char memory_value_text[128] = "0";

void MemoryRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Switch to 3D rendering (Scene)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, winW/winH, 0.01, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam.x, cam.y, cam.z,
            cam.lx, cam.ly, cam.lz,
            0.0, 1.0, 0.0);

	SkyRender();
	RenderFloor();

	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0.0);
    glColor3f(0.2, 0.3, 0.4);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 3.0, 0.0);
    glVertex3f(1.0, 3.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();

    glColor3f(0.5, 0.6, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, memory_value, 0.0);
    glVertex3f(1.0, memory_value, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();
	glPopMatrix();

	FontRender(0.2, memory_value, 0.0, memory_value_text);

	// Switch to 2D rendering (HUD)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, winW, 0.0, winH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (terminal_visible)
        TerminalRender();

    SDL_GL_SwapWindow(window);
}

