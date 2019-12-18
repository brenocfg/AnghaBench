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

void
js_fmtexp(char *p, int e)
{
	char se[9];
	int i;

	*p++ = 'e';
	if(e < 0) {
		*p++ = '-';
		e = -e;
	} else
		*p++ = '+';
	i = 0;
	while(e) {
		se[i++] = e % 10 + '0';
		e /= 10;
	}
	while(i < 1)
		se[i++] = '0';
	while(i > 0)
		*p++ = se[--i];
	*p++ = '\0';
}