#include <3ds.h>

Result sd_init();
Result sd_exit();
bool sd_fileExists(char* asciipath);
int sd_getFileSize(char *asciipath);
int sd_quickRead(char* asciipath, size_t size, void* out);
int sd_quickWrite(char* asciipath, void* out, size_t writesize);