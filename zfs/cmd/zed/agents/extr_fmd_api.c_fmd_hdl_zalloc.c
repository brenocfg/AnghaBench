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
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 void* umem_zalloc (size_t,int) ; 

void *
fmd_hdl_zalloc(fmd_hdl_t *hdl, size_t size, int flags)
{
	return (umem_zalloc(size, flags));
}