#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */

__attribute__((used)) static 
void applySavedTimeInfoToOutputFile ( Char *dstName )
{
#  if BZ_UNIX
   IntNative      retVal;
   struct utimbuf uTimBuf;

   uTimBuf.actime = fileMetaInfo.st_atime;
   uTimBuf.modtime = fileMetaInfo.st_mtime;

   retVal = utime ( dstName, &uTimBuf );
   ERROR_IF_NOT_ZERO ( retVal );
#  endif
}