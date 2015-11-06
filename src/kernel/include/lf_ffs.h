#ifndef _LF_FFS_H_INCLUDED
#define _LF_FFS_H_INCLUDED

#include <stdint.h>
#include <string.h>

typedef struct
{
    uint32_t magic;
    uint16_t verMajor;
    uint16_t verMinor;
    uint64_t countFiles;
    uint8_t fsName[255];
    uint8_t oemName[31];
} PACKED LF_FFS_HEADER_T;

typedef struct
{
    uint64_t size;
    uint32_t attributes;
    uint8_t filename[255];
    uint64_t offset;
} PACKED LF_FFS_ENTRY_T;

#define LF_FFS_MagicNumber ('L' | ('F' << 8) | ('3' << 16) | ('S' << 24))

class LF_FFS
{
public:
    LF_FFS(char *buffer);

    uint64_t get_CountFiles();
    LF_FFS_ENTRY_T *get_Files();

    bool get_Valid();

    void *getFileBufferAddr(char *fileName);
    int getFileSize(char *fileName);

private:
    LF_FFS_ENTRY_T _files[1024];
    LF_FFS_HEADER_T _header;
    bool _isValid;
    char *_buffer;
};

#endif
