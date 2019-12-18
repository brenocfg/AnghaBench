#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* mod_spec; } ;
typedef  TYPE_1__ fmd_module_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */

void
fmd_hdl_setspecific(fmd_hdl_t *hdl, void *spec)
{
	fmd_module_t *mp = (fmd_module_t *)hdl;

	mp->mod_spec = spec;
}