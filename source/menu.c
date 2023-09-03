#include "menu.h"

enum mainstates {
    STATE_FIRST,
    STATE_PREP,
    STATE_INITIAL,
    STATE_FIRST_LAUNCH1,
    STATE_FIRST_LAUNCH2,
    STATE_DISPLAY_BOX,
    STATE_EXIT
};


struct boxState {
    int retstate1;
    int retstate2;
    char text[DISPLAY_MAX_SIZE];
    bool yesnomode;
    char b1[BUTTON_MAX_STRLEN];
    char b2[BUTTON_MAX_STRLEN];
};

static int state = STATE_PREP;
static DrawContext ctx;
bool shouldExit = false;
struct boxState curbox;
touchPosition touch;
Button ret1, ret2;

void errorDisplay(const char* format, ...) {
    char buffer[ERROR_BUF_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf (buffer, ERROR_BUF_SIZE, format, args);
    drawTextCentered(10.0f, 200.0f, 0.0f, 1.0f, ctx.clrWhite, buffer);
}

void menu_init() {
    gfxInitDefault();
    initUI();
    initContext(&ctx);
    initColors(&ctx);
    newButton(&ret1, 0+1, 200+1, 0, 160-2, 40-2, "OK", 0.0f, ctx.clrWhite, ctx.clrBgBright, 1.0f);
    newButton(&ret2, 160+1, 200+1, 0, 160-2, 40-2, "OK", 0.0f, ctx.clrWhite, ctx.clrBgBright, 1.0f);
}

void menu_exit() {
    exitUI();
    gfxExit();
}

bool menu_shouldExit() {
    return shouldExit;
}

static void drawMenuTop() {
    switch(state) {
        case STATE_PREP:
            drawTextCentered(200.0f, 105.0f, 0.0f, 1.0f, ctx.clrWhite, "Preparing...");
    }
}

static void drawMenuBottom() {
    switch(state) {
        case STATE_DISPLAY_BOX:
            drawTextCentered(SCREEN_WIDTH_BOTTOM/2, 20, 0, 1.0f, ctx.clrWhite, curbox.text);
            drawButton(&ret1);
            drawButton(&ret2);
    }
}

static void setBoxStruct(int retstate1, int retstate2, char* text, bool yesnomode, char* b1, char* b2) {
    curbox.retstate1 = retstate1;
    if (yesnomode) curbox.retstate2 = retstate2;
    snprintf(curbox.text, DISPLAY_MAX_SIZE, text);
    snprintf(curbox.b1, BUTTON_MAX_STRLEN, b1);
    if (yesnomode) snprintf(curbox.b2, BUTTON_MAX_STRLEN, b2);
    curbox.yesnomode = yesnomode;
}

void menu_update() {
    hidScanInput();
    hidTouchRead(&touch);
    switch(state) {
        case STATE_FIRST:
            state = STATE_PREP;
            break;
        case STATE_PREP:
            if (sd_fileExists("/gravemanager/config.json")) {
                state = STATE_INITIAL;
            } else {
                state = STATE_FIRST_LAUNCH1;
            }
            break;
        case STATE_FIRST_LAUNCH1:
            setBoxStruct(STATE_FIRST_LAUNCH2, STATE_EXIT, "Preparing for first launch", true, "OK", "get me out");
            state = STATE_DISPLAY_BOX;
            break;
        case STATE_FIRST_LAUNCH2:
        case STATE_DISPLAY_BOX:
            changeButtonString(&ret1, curbox.b1);
            changeButtonString(&ret2, curbox.b2);
            if (isButtonPressed(&ret1)) {
                state = curbox.retstate1;
                break;
            }
            if (isButtonPressed(&ret2) && curbox.yesnomode) {
                state = curbox.retstate2;
                break;
            }
            break;
        case STATE_EXIT:
            shouldExit = true;
            break;
        
        

    }


    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_TargetClear(ctx.top, ctx.clrBgDark);
    C2D_TargetClear(ctx.bottom, ctx.clrBgDark);
    C2D_SceneBegin(ctx.top);
    drawMenuTop();
    C2D_SceneBegin(ctx.bottom);
    drawMenuBottom();
    C3D_FrameEnd(0);
}



