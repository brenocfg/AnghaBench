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
void saveInputFileMetaInfo ( Char *srcName )
{
#  if BZ_UNIX
   IntNative retVal;
   /* Note use of stat here, not lstat. */
   retVal = MY_STAT( srcName, &fileMetaInfo );
   ERROR_IF_NOT_ZERO ( retVal );
#  endif
}