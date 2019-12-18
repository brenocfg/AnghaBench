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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int write_data (int /*<<< orphan*/ *,int,unsigned char*,int) ; 

int write_partition_physical_disk_drive_id_fat32(FILE *fp)
{
   unsigned char ucId = 0x80; /* C: */

   return write_data(fp, 0x40, &ucId, 1);
}