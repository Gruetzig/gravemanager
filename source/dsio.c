#include "dsio.h"

FS_Archive twlnArchive;

Result mountDSiParition() {
    return FSUSER_OpenArchive(&twlnArchive, ARCHIVE_NAND_TWL_FS, fsMakePath(PATH_EMPTY, ""));
}

