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
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int INT_MAX ; 

int js_isarrayindex(js_State *J, const char *p, int *idx)
{
	int n = 0;
	while (*p) {
		int c = *p++;
		if (c >= '0' && c <= '9') {
			if (n >= INT_MAX / 10)
				return 0;
			n = n * 10 + (c - '0');
		} else {
			return 0;
		}
	}
	return *idx = n, 1;
}