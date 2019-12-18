#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WRes ;
struct TYPE_3__ {int /*<<< orphan*/  file; int /*<<< orphan*/  handle; } ;
typedef  size_t DWORD ;
typedef  TYPE_1__ CSzFile ;
typedef  int /*<<< orphan*/  Byte ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,void*,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ ) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ ) ; 
 size_t kChunkSizeMax ; 

WRes File_Read(CSzFile *p, void *data, size_t *size)
{
  size_t originalSize = *size;
  if (originalSize == 0)
    return 0;

  #ifdef USE_WINDOWS_FILE

  *size = 0;
  do
  {
    DWORD curSize = (originalSize > kChunkSizeMax) ? kChunkSizeMax : (DWORD)originalSize;
    DWORD processed = 0;
    BOOL res = ReadFile(p->handle, data, curSize, &processed, NULL);
    data = (void *)((Byte *)data + processed);
    originalSize -= processed;
    *size += processed;
    if (!res)
      return GetLastError();
    if (processed == 0)
      break;
  }
  while (originalSize > 0);
  return 0;

  #else
  
  *size = fread(data, 1, originalSize, p->file);
  if (*size == originalSize)
    return 0;
  return ferror(p->file);
  
  #endif
}