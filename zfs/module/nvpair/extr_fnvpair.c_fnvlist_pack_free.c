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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kmem_free (char*,size_t) ; 

void
fnvlist_pack_free(char *pack, size_t size)
{
#ifdef _KERNEL
	kmem_free(pack, size);
#else
	free(pack);
#endif
}