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
 int /*<<< orphan*/  pathtable_get_size_and_entries (void const*,unsigned int*,int /*<<< orphan*/ *) ; 

unsigned int
iso9660_pathtable_get_size (const void *pt)
{
  unsigned int size = 0;
  pathtable_get_size_and_entries (pt, &size, NULL);
  return size;
}