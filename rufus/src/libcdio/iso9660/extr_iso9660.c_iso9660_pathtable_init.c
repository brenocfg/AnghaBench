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
typedef  int /*<<< orphan*/  iso_path_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISO_BLOCKSIZE ; 
 int /*<<< orphan*/  cdio_assert (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
iso9660_pathtable_init (void *pt)
{
  cdio_assert (sizeof (iso_path_table_t) == 8);

  cdio_assert (pt != NULL);

  memset (pt, 0, ISO_BLOCKSIZE); /* fixme */
}