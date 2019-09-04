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
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
gl_tab(char *buf, int offset, int *loc, size_t bufsize)
/* default tab handler, acts like tabstops every 8 cols */
{
    int i, count, len;

    len = (int) strlen(buf);
    count = 8 - (offset + *loc) % 8;
    for (i=len; i >= *loc; i--)
    	if (i+count < (int) bufsize)
		buf[i+count] = buf[i];
    for (i=0; i < count; i++)
    	if (*loc+i < (int) bufsize)
		buf[*loc+i] = ' ';
    i = *loc;
    *loc = i + count;
    return i;
}