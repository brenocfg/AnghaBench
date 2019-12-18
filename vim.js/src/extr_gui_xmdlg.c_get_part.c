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

__attribute__((used)) static void
get_part(char *in, int pos, char *out)
{
    int	i;
    int j;

    *out = '\0';

    for (i = 0; (pos > 0) && (in[i] != '\0'); ++i)
	if (in[i] == '-')
	    pos--;

    if (in[i] == '\0')
	return;

    for (j = 0; (in[i] != '-') && (in[i] != '\0'); ++i, ++j)
	out[j] = in[i];
    out[j] = '\0';
}