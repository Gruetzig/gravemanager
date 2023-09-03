#include "configuration.h"

static char *configI_LaunchPath = "";

void config_setLaunchPath(char* argv0) {
    configI_LaunchPath = argv0;
}

char* config_getLaunchPath() {
    return configI_LaunchPath;
}