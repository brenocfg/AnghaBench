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
typedef  int /*<<< orphan*/  nv_alloc_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (void*,size_t) ; 

__attribute__((used)) static void
nv_free_sys(nv_alloc_t *nva, void *buf, size_t size)
{
	kmem_free(buf, size);
}