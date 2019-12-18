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
 int Runeself ; 
 int /*<<< orphan*/  fz_chartorune (int*,char const*) ; 

int
fz_utflen(const char *s)
{
	int c, n, rune;
	n = 0;
	for(;;) {
		c = *(const unsigned char*)s;
		if(c < Runeself) {
			if(c == 0)
				return n;
			s++;
		} else
			s += fz_chartorune(&rune, s);
		n++;
	}
	return 0;
}