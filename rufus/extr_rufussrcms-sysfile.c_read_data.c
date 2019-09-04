#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int _offset; int /*<<< orphan*/  _handle; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ FAKE_FD ;

/* Variables and functions */
 int MAX_DATA_LEN ; 
 int /*<<< orphan*/  _mm_free (unsigned char*) ; 
 unsigned char* _mm_malloc (int,int) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,size_t) ; 
 scalar_t__ read_sectors (int /*<<< orphan*/ ,int,int,int,unsigned char*) ; 
 int ulBytesPerSector ; 
 int /*<<< orphan*/  uprintf (char*) ; 

int read_data(FILE *fp, uint64_t Position,
              void *pData, uint64_t Len)
{
   int r = 0;
   unsigned char *aucBuf = _mm_malloc(MAX_DATA_LEN, 16);
   FAKE_FD* fd = (FAKE_FD*)fp;
   HANDLE hDrive = (HANDLE)fd->_handle;
   uint64_t StartSector, EndSector, NumSectors;

   if (aucBuf == NULL)
      return 0;

   Position += fd->_offset;

   StartSector = Position/ulBytesPerSector;
   EndSector   = (Position+Len+ulBytesPerSector -1)/ulBytesPerSector;
   NumSectors  = (size_t)(EndSector - StartSector);

   if((NumSectors*ulBytesPerSector) > MAX_DATA_LEN)
   {
      uprintf("read_data: Please increase MAX_DATA_LEN in file.h\n");
      goto out;
   }

   if(Len > 0xFFFFFFFFUL)
   {
      uprintf("read_data: Len is too big\n");
      goto out;
   }

   if(read_sectors(hDrive, ulBytesPerSector, StartSector,
                     NumSectors, aucBuf) <= 0)
   goto out;

   memcpy(pData, &aucBuf[Position - StartSector*ulBytesPerSector], (size_t)Len);

   r = 1;

out:
   _mm_free(aucBuf);
   return r;
}