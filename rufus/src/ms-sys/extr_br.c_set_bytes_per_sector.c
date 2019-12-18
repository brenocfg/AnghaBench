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

/* Variables and functions */
 int ulBytesPerSector ; 

void set_bytes_per_sector(unsigned long ulValue)
{
   ulBytesPerSector = ulValue;
   if ((ulBytesPerSector < 512) || (ulBytesPerSector > 65536))
      ulBytesPerSector = 512;
}