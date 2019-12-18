#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  long int32_t ;
struct TYPE_3__ {int hasError; int /*<<< orphan*/  isQuiet; scalar_t__ isAutoSpacing; scalar_t__ isBinary; int /*<<< orphan*/  isReadable; } ;
struct TYPE_4__ {int longSize; TYPE_1__ file; int /*<<< orphan*/ * handle; int /*<<< orphan*/  isNativeEncoding; } ;
typedef  int /*<<< orphan*/  THFile ;
typedef  TYPE_2__ THDiskFile ;

/* Variables and functions */
 int EOF ; 
 long* THAlloc (int) ; 
 int /*<<< orphan*/  THArgCheck (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  THDiskFile_isLittleEndianCPU () ; 
 int /*<<< orphan*/  THDiskFile_reverseMemory (long*,long*,int,size_t) ; 
 int /*<<< orphan*/  THError (char*,size_t,size_t) ; 
 int /*<<< orphan*/  THFree (long*) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 size_t fread__ (long*,int,size_t,int /*<<< orphan*/ *) ; 
 int fscanf (int /*<<< orphan*/ *,char*,long*) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t THDiskFile_readLong(THFile *self, long *data, size_t n)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  size_t nread = 0L;

  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  THArgCheck(dfself->file.isReadable, 1, "attempt to read in a write-only file");

  if(dfself->file.isBinary)
  {
    if(dfself->longSize == 0 || dfself->longSize == sizeof(long))
    {
      nread = fread__(data, sizeof(long), n, dfself->handle);
      if(!dfself->isNativeEncoding && (sizeof(long) > 1) && (nread > 0))
        THDiskFile_reverseMemory(data, data, sizeof(long), nread);
    } else if(dfself->longSize == 4)
    {
      nread = fread__(data, 4, n, dfself->handle);
      if(!dfself->isNativeEncoding && (nread > 0))
        THDiskFile_reverseMemory(data, data, 4, nread);
      size_t i;
      for(i = nread; i > 0; i--)
        data[i-1] = ((int *)data)[i-1];
    }
    else /* if(dfself->longSize == 8) */
    {
      int big_endian = !THDiskFile_isLittleEndianCPU();
      int32_t *buffer = THAlloc(8*n);
      nread = fread__(buffer, 8, n, dfself->handle);
      size_t i;
      for(i = nread; i > 0; i--)
        data[i-1] = buffer[2*(i-1) + big_endian];
      THFree(buffer);
      if(!dfself->isNativeEncoding && (nread > 0))
        THDiskFile_reverseMemory(data, data, 4, nread);
     }
  }
  else
  {
    size_t i;
    for(i = 0; i < n; i++)
    {
      int ret = fscanf(dfself->handle, "%ld", &data[i]); if(ret <= 0) break; else nread++;
    }
    if(dfself->file.isAutoSpacing && (n > 0))
    {
      int c = fgetc(dfself->handle);
      if( (c != '\n') && (c != EOF) )
        ungetc(c, dfself->handle);
    }
  }

  if(nread != n)
  {
    dfself->file.hasError = 1; /* shouldn't we put hasError to 0 all the time ? */
    if(!dfself->file.isQuiet)
      THError("read error: read %d blocks instead of %d", nread, n);
  }

  return nread;
}