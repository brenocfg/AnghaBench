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

/* Variables and functions */
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

void
fnvlist_add_nvlist(nvlist_t *nvl, const char *name, nvlist_t *val)
{
	VERIFY0(nvlist_add_nvlist(nvl, name, val));
}