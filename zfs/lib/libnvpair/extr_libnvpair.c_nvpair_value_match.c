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
typedef  int /*<<< orphan*/  nvpair_t ;

/* Variables and functions */
 int nvpair_value_match_regex (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,char**) ; 

int
nvpair_value_match(nvpair_t *nvp, int ai, char *value, char **ep)
{
	return (nvpair_value_match_regex(nvp, ai, value, NULL, ep));
}