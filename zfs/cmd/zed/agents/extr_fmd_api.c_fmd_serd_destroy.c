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
struct TYPE_2__ {int /*<<< orphan*/  mod_serds; } ;
typedef  TYPE_1__ fmd_module_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fmd_serd_eng_delete (int /*<<< orphan*/ *,char const*) ; 

void
fmd_serd_destroy(fmd_hdl_t *hdl, const char *name)
{
	fmd_module_t *mp = (fmd_module_t *)hdl;

	fmd_serd_eng_delete(&mp->mod_serds, name);

	fmd_hdl_debug(hdl, "serd_destroy %s", name);
}