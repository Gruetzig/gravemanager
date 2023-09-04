#include <3ds.h>
#include <citro2d.h>
#include <stdarg.h>

#include "ui.h"
#include "sd.h"
#include "bth.h"

#define ERROR_BUF_SIZE 256
#define DISPLAY_MAX_SIZE 256
#define BUTTON_MAX_STRLEN 12
#define ACTIONTEXT_MAX_SIZE 2048

bool menu_shouldExit();
void menu_init();
void menu_exit();
void menu_draw();
void menu_update();