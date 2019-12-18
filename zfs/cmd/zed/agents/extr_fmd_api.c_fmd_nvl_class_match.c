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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  FM_CLASS ; 
 scalar_t__ fmd_strmatch (char*,char const*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 

int
fmd_nvl_class_match(fmd_hdl_t *hdl, nvlist_t *nvl, const char *pattern)
{
	char *class;

	return (nvl != NULL &&
	    nvlist_lookup_string(nvl, FM_CLASS, &class) == 0 &&
	    fmd_strmatch(class, pattern));
}