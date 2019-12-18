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
typedef  int /*<<< orphan*/  scan_io_t ;
typedef  int /*<<< orphan*/  dva_t ;

/* Variables and functions */
 int SPA_DVAS_PER_BP ; 
 int /*<<< orphan*/  fill_weight ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sio_cache ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  zfs_scan_fill_weight ; 

void
scan_init(void)
{
	/*
	 * This is used in ext_size_compare() to weight segments
	 * based on how sparse they are. This cannot be changed
	 * mid-scan and the tree comparison functions don't currently
	 * have a mechanism for passing additional context to the
	 * compare functions. Thus we store this value globally and
	 * we only allow it to be set at module initialization time
	 */
	fill_weight = zfs_scan_fill_weight;

	for (int i = 0; i < SPA_DVAS_PER_BP; i++) {
		char name[36];

		(void) sprintf(name, "sio_cache_%d", i);
		sio_cache[i] = kmem_cache_create(name,
		    (sizeof (scan_io_t) + ((i + 1) * sizeof (dva_t))),
		    0, NULL, NULL, NULL, NULL, NULL, 0);
	}
}