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
typedef  int /*<<< orphan*/  Rune ;

/* Variables and functions */
 int canon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chartorune (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int strncmpcanon(const char *a, const char *b, int n)
{
	Rune ra, rb;
	int c;
	while (n--) {
		if (!*a) return -1;
		if (!*b) return 1;
		a += chartorune(&ra, a);
		b += chartorune(&rb, b);
		c = canon(ra) - canon(rb);
		if (c)
			return c;
	}
	return 0;
}