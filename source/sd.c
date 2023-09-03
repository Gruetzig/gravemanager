#include "sd.h"

static FS_Archive sdmcArchive;

Result sd_init() {
    return FSUSER_OpenArchive(&sdmcArchive, MEDIATYPE_SD, fsMakePath(PATH_EMPTY, ""));
}

Result sd_exit() {
    return FSUSER_CloseArchive(sdmcArchive);
}

bool sd_fileExists(char* asciipath) {
    Handle file;
    Result ret;
    ret = FSUSER_OpenFile(&file, sdmcArchive, fsMakePath(PATH_ASCII, asciipath), FS_OPEN_READ, 0);
    if (ret) {
        return false;
    } else 
    FSFILE_Close(file);
    return true;
}

int sd_getFileSize(char *asciipath) {
    Handle file;
    u64 fsize;
    Result result;
    result = FSUSER_OpenFile(&file, sdmcArchive, fsMakePath(PATH_ASCII, asciipath), FS_OPEN_READ, 0);
    if (result) {
        return -1;
    }
    result = FSFILE_GetSize(file, &fsize);
    if (result) {
        FSFILE_Close(file);
        return -2;
    }
    result = FSFILE_Close(file);
    if (result) {
        return -3;
    }
    return fsize;
}

int sd_quickRead(char* asciipath, size_t size, void* out)  {
    Handle file;
    Result result;
    u32 bytesread;
    result = FSUSER_OpenFile(&file, sdmcArchive, fsMakePath(PATH_ASCII, asciipath), FS_OPEN_READ, 0);
    if (result) {
        return -1;
    }
    result = FSFILE_Read(file, &bytesread, 0, out, size);
    if (result) {
        FSFILE_Close(file);
        return -2;
    }
    result = FSFILE_Close(file);
    if (result) {
        return -3;
    }
    return bytesread;
}

int sd_quickWrite(char* asciipath, void* out, size_t writesize) {
    Handle file;
    Result result;
    u32 byteswritten;
    result = FSUSER_OpenFile(&file, sdmcArchive, fsMakePath(PATH_ASCII, asciipath), FS_OPEN_WRITE | FS_OPEN_CREATE, 0);
    if (result) {
        return -1;
    }
    result = FSFILE_Write(file, &byteswritten, 0, out, writesize, FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME);
    if (result) {
        FSFILE_Close(file);
        return -2;
    }
    result = FSFILE_Close(file);
    if (result) {
        return -3;
    }
    return byteswritten;
}

