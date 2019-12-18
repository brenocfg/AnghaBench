#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* pd_name; char* pd_colname; } ;
typedef  TYPE_1__ zprop_desc_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 int B_TRUE ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 char const tolower (char const) ; 

__attribute__((used)) static boolean_t
propname_match(const char *p, size_t len, zprop_desc_t *prop_entry)
{
	const char *propname = prop_entry->pd_name;
#ifndef _KERNEL
	const char *colname = prop_entry->pd_colname;
	int c;
#endif

	if (len == strlen(propname) &&
	    strncmp(p, propname, len) == 0)
		return (B_TRUE);

#ifndef _KERNEL
	if (colname == NULL || len != strlen(colname))
		return (B_FALSE);

	for (c = 0; c < len; c++)
		if (p[c] != tolower(colname[c]))
			break;

	return (colname[c] == '\0');
#else
	return (B_FALSE);
#endif
}