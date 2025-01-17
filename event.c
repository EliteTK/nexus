#include <SDL2/SDL.h>

#include "nexus.h"

unsigned int mods;
unsigned int show_keys;
int mouse_x, mouse_y, mouse_x_prev, mouse_y_prev;
unsigned int mouse_button, mouse_held;
SDL_Event event;

void EventCheck(void) {
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			mainloopend = 1;
		else if (event.type == SDL_KEYDOWN) {
			if (show_keys)
				printf("key: %s\n", SDL_GetKeyName(event.key.keysym.sym));

//			if (terminal_visible && (event.key.keysym.sym >= ' ' && 
//				event.key.keysym.sym <= '~')) {
			if (terminal_visible && (event.key.keysym.sym >= SDLK_SPACE && 
				event.key.keysym.sym <= SDLK_z)) {
				terminal_buffer[terminal_cursor_pos++] = event.key.keysym.sym;
				return;
			}
			else if (terminal_visible && event.key.keysym.sym == SDLK_BACKSPACE) {
				if (terminal_cursor_pos > 0)
					terminal_buffer[--terminal_cursor_pos] = '\0';
				return;
			}
			else if (terminal_visible && event.key.keysym.sym == SDLK_RETURN) {
				TerminalParse();
				return;
			}
			
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				mainloopend = 1;
				break;
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				mods |= MOD_CTRL;
				break;
			case SDLK_LALT:
			case SDLK_RALT:
				mods |= MOD_ALT;
				break;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				mods |= MOD_SHIFT;
				break;
			case SDLK_TAB:
				terminal_visible = !terminal_visible;
				break;
			case SDLK_UP:
				cam.moving |= MOVE_FRONT;
				break;
			case SDLK_DOWN:
				cam.moving |= MOVE_BACK;
				break;
			case SDLK_LEFT:
				cam.moving |= MOVE_LEFT;
				break;
			case SDLK_RIGHT:
				cam.moving |= MOVE_RIGHT;
				break;
			case SDLK_PAGEUP:
				cam.moving |= MOVE_UP;
				break;
			case SDLK_PAGEDOWN:
				cam.moving |= MOVE_DOWN;
				break;
			case SDLK_F1:
				StateSet(STATE_MAIN);
				break;
			case SDLK_b:
				if (state != STATE_BROWSER)
					StateSet(STATE_BROWSER);
				else
					StateSet(state_prev);
				break;
			case SDLK_e:
				if (state != STATE_EDITOR)
					StateSet(STATE_EDITOR);
				else
					StateSet(state_prev);
				break;
			case SDLK_k:
				show_keys = !show_keys;
				break;
			case SDLK_m:
				if (state != STATE_MEMORY)
					StateSet(STATE_MEMORY);
				else
					StateSet(state_prev);
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch(event.key.keysym.sym) {
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				mods ^= MOD_CTRL;
				break;
			case SDLK_LALT:
			case SDLK_RALT:
				mods ^= MOD_ALT;
				break;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				mods ^= MOD_SHIFT;
				break;
			case SDLK_UP:
				cam.moving ^= MOVE_FRONT;
				break;
			case SDLK_DOWN:
				cam.moving ^= MOVE_BACK;
				break;
			case SDLK_LEFT:
				cam.moving ^= MOVE_LEFT;
				break;
			case SDLK_RIGHT:
				cam.moving ^= MOVE_RIGHT;
				break;
			case SDLK_PAGEUP:
				cam.moving ^= MOVE_UP;
				break;
			case SDLK_PAGEDOWN:
				cam.moving ^= MOVE_DOWN;
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_RIGHT)
				mouse_held = !mouse_held;

			if (mouse_held) {
				mouse_x_prev = mouse_x = (int)winW/2;
				mouse_y_prev = mouse_y = (int)winH/2;
				SDL_WarpMouseInWindow(window, mouse_x, mouse_y);
			}
		}
		else if (event.type == SDL_MOUSEMOTION) {
			SDL_GetMouseState(&mouse_x, &mouse_y);

			if (mouse_held) {
				if (mouse_x - mouse_x_prev > 0) {
					CameraRotateStep(0.01);
				}
				else if (mouse_x - mouse_x_prev < 0) {
					CameraRotateStep(-0.01);
				}

				mouse_x = (int)winW/2;
				mouse_y = (int)winH/2;
				SDL_WarpMouseInWindow(window, mouse_x, mouse_y);
			}
			else {
				mouse_x_prev = mouse_x;
				mouse_y_prev = mouse_y;
			}
		}
	}
}

