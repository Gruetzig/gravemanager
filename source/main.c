#include <3ds.h>
#include <citro2d.h>
#include "menu.h"
#include "configuration.h"

int main(int argc, char* argv[]) {
    config_setLaunchPath(argv[0]);
    menu_init();
    while(aptMainLoop()) {

        menu_update();

        if (menu_shouldExit()) {
            break;
        }
    }
    menu_exit();
    return 0;
}
