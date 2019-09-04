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
typedef  char xmlChar ;

/* Variables and functions */

const xmlChar *
xmlSplitQName3(const xmlChar *name, int *len) {
    int l = 0;

    if (name == NULL) return(NULL);
    if (len == NULL) return(NULL);

    /* nasty but valid */
    if (name[0] == ':')
	return(NULL);

    /*
     * we are not trying to validate but just to cut, and yes it will
     * work even if this is as set of UTF-8 encoded chars
     */
    while ((name[l] != 0) && (name[l] != ':'))
	l++;

    if (name[l] == 0)
	return(NULL);

    *len = l;

    return(&name[l+1]);
}