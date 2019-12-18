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
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,char const*) ; 

void
fmd_case_uuresolved(fmd_hdl_t *hdl, const char *uuid)
{
	fmd_hdl_debug(hdl, "case resolved by uuid (%s)", uuid);
}