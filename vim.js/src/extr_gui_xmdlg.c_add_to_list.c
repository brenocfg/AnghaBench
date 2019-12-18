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

/* Variables and functions */
 int MAX_ENTRIES_IN_LIST ; 
 char* XtNewString (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* wild ; 

__attribute__((used)) static void
add_to_list(char **buf, char *item, int *count)
{
    int	i;
    int j;

    if (*count == MAX_ENTRIES_IN_LIST)
	return;

    /* avoid duplication */
    for (i = 0; i < *count; ++i)
    {
	if (!strcmp(buf[i], item))
	    return;
    }

    /* find order place, but make sure that wild card comes first */
    if (!strcmp(item, wild))
	i = 0;
    else
	for (i = 0; i < *count; ++i)
	    if (strcmp(buf[i], item) > 0 && strcmp(buf[i], wild))
		break;

    /* now insert the item */
    for (j = *count; j > i; --j)
	buf[j] = buf[j-1];
    buf[i] = XtNewString(item);

    ++(*count);
}