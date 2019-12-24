#ifndef __flashFS_h_INCLUDED__
#define __flashFS_h_INCLUDED__

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct 
{
  char root[32];
  char partition[17];
  uint8_t maxOpenFiles;
} FlashFSConfig_t;


void flashFSInit(FlashFSConfig_t* config);
void flashFSInfo(size_t* total, size_t* used, size_t* totalFlashMem);
#endif