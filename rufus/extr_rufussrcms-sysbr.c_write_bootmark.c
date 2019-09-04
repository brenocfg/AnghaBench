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
typedef  int /*<<< orphan*/  aucRef ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned long ulBytesPerSector ; 
 int /*<<< orphan*/  write_data (int /*<<< orphan*/ *,unsigned long,unsigned char*,int) ; 

__attribute__((used)) static int write_bootmark(FILE *fp)
{
   unsigned char aucRef[] = {0x55, 0xAA};
   unsigned long pos = 0x1FE;

   for (pos = 0x1FE; pos < ulBytesPerSector; pos += 0x200) {
      if (!write_data(fp, pos, aucRef, sizeof(aucRef)))
		    return 0;
   }
   return 1;
}