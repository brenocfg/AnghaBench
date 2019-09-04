#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long int32_t ;
struct TYPE_5__ {int hasError; int /*<<< orphan*/  isQuiet; scalar_t__ isAutoSpacing; scalar_t__ isBinary; int /*<<< orphan*/  isReadable; } ;
struct TYPE_6__ {int longSize; scalar_t__ position; scalar_t__ size; TYPE_2__ file; TYPE_1__* storage; } ;
struct TYPE_4__ {char* data; } ;
typedef  TYPE_3__ THMemoryFile ;
typedef  int /*<<< orphan*/  THFile ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  THArgCheck (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  THDiskFile_isLittleEndianCPU () ; 
 int /*<<< orphan*/  THError (char*,size_t,size_t) ; 
 char* THMemoryFile_strnextspace (char*,char*) ; 
 int /*<<< orphan*/  memmove (long*,char*,size_t) ; 
 int sscanf (char*,char*,long*,int*) ; 

__attribute__((used)) static size_t THMemoryFile_readLong(THFile *self, long *data, size_t n)
{
  THMemoryFile *mfself = (THMemoryFile*)self;
  size_t nread = 0L;

  THArgCheck(mfself->storage != NULL, 1, "attempt to use a closed file");
  THArgCheck(mfself->file.isReadable, 1, "attempt to read in a write-only file");

  if (n == 0)
    return 0;

  if(mfself->file.isBinary)
  {
    if(mfself->longSize == 0 || mfself->longSize == sizeof(long))
    {
      size_t nByte = sizeof(long)*n;
      size_t nByteRemaining = (mfself->position + nByte <= mfself->size ? nByte : mfself->size-mfself->position);
      nread = nByteRemaining/sizeof(long);
      memmove(data, mfself->storage->data+mfself->position, nread*sizeof(long));
      mfself->position += nread*sizeof(long);
    } else if(mfself->longSize == 4)
    {
      size_t nByte = 4*n;
      size_t nByteRemaining = (mfself->position + nByte <= mfself->size ? nByte : mfself->size-mfself->position);
      int32_t *storage = (int32_t *)(mfself->storage->data + mfself->position);
      nread = nByteRemaining/4;
      size_t i;
      for(i = 0; i < nread; i++)
        data[i] = storage[i];
      mfself->position += nread*4;
    }
    else /* if(mfself->longSize == 8) */
    {
      int big_endian = !THDiskFile_isLittleEndianCPU();
      size_t nByte = 8*n;
      int32_t *storage = (int32_t *)(mfself->storage->data + mfself->position);
      size_t nByteRemaining = (mfself->position + nByte <= mfself->size ? nByte : mfself->size-mfself->position);
      nread = nByteRemaining/8;
      size_t i;
      for(i = 0; i < nread; i++)
        data[i] = storage[2*i + big_endian];
      mfself->position += nread*8;
    }
  }
  else
  {
    size_t i;
    for(i = 0; i < n; i++)
    {
      size_t nByteRead = 0;
      char spaceChar = 0;
      char *spacePtr = THMemoryFile_strnextspace(mfself->storage->data+mfself->position, &spaceChar);
      int nByteRead_; int ret = sscanf(mfself->storage->data+mfself->position, "%ld%n", &data[i], &nByteRead_); nByteRead = nByteRead_; if(ret <= 0) break; else nread++;
      if(ret == EOF)
      {
        while(mfself->storage->data[mfself->position])
          mfself->position++;
      }
      else
        mfself->position += nByteRead;
      if(spacePtr)
        *spacePtr = spaceChar;
    }
    if(mfself->file.isAutoSpacing && (n > 0))
    {
      if( (mfself->position < mfself->size) && (mfself->storage->data[mfself->position] == '\n') )
        mfself->position++;
    }
  }

  if(nread != n)
  {
    mfself->file.hasError = 1; /* shouldn't we put hasError to 0 all the time ? */
    if(!mfself->file.isQuiet)
      THError("read error: read %d blocks instead of %d", nread, n);
  }

  return nread;
}