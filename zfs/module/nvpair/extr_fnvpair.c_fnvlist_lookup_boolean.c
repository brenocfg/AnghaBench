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
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ nvlist_lookup_boolean (int /*<<< orphan*/ *,char const*) ; 

boolean_t
fnvlist_lookup_boolean(nvlist_t *nvl, const char *name)
{
	return (nvlist_lookup_boolean(nvl, name) == 0);
}