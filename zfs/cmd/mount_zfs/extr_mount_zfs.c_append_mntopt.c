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
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int MNT_LINE_MAX ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 

__attribute__((used)) static void
append_mntopt(const char *name, const char *val, char *mntopts,
    char *mtabopt, boolean_t quote)
{
	char tmp[MNT_LINE_MAX];

	snprintf(tmp, MNT_LINE_MAX, quote ? ",%s=\"%s\"" : ",%s=%s", name, val);

	if (mntopts)
		strlcat(mntopts, tmp, MNT_LINE_MAX);

	if (mtabopt)
		strlcat(mtabopt, tmp, MNT_LINE_MAX);
}