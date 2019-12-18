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
typedef  int Rune ;

/* Variables and functions */
 int Runeself ; 
 int /*<<< orphan*/  chartorune (int*,char const*) ; 

int js_runeat(js_State *J, const char *s, int i)
{
	Rune rune = 0;
	while (i-- >= 0) {
		rune = *(unsigned char*)s;
		if (rune < Runeself) {
			if (rune == 0)
				return 0;
			++s;
		} else
			s += chartorune(&rune, s);
	}
	return rune;
}