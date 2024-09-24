#ifdef SFS_H
#define SFS_H
    struct metaBlock{
        char *filename;
        char *filetype;
        char *permissions;
        void **dataBlockHeads;
        void **dataBlockTails;
    }
#endif
