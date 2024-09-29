#ifndef SFS_H
#define SFS_H
    #define BLOCK_SIZE (1<<16)

    #define FILENAME_SIZE_BYTES (64)
    #define FILETYPE_SIZE_BYTES (2)
    #define PERMISSIONS_ARRAY_SIZE_BYTES (10)

    #define DATABLOCK_PTR_ARRAY_SIZE_BYTES (((BLOCK_SIZE - FILENAME_SIZE_BYTES - FILETYPE_SIZE_BYTES - PERMISSIONS_ARRAY_SIZE_BYTES)/2/sizeof(void*)))

    struct metaBlock{
        char filename        [FILENAME_SIZE_BYTES];
        char filetype        [FILETYPE_SIZE_BYTES];
        char permissions     [PERMISSIONS_ARRAY_SIZE_BYTES];
        void *dataBlockHeads [DATABLOCK_PTR_ARRAY_SIZE_BYTES];
        void *dataBlockTails [DATABLOCK_PTR_ARRAY_SIZE_BYTES];
    };
#endif
