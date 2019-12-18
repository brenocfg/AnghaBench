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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  read_data (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

uint32_t read_windows_disk_signature(FILE *fp)
{
   uint32_t tWDS;
   if(!read_data(fp, 0x1b8, &tWDS, 4))
      return 0;
   return tWDS;
}