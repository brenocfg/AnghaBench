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
typedef  unsigned char Rune ;

/* Variables and functions */
 unsigned char Runeself ; 
 int /*<<< orphan*/  chartorune (unsigned char*,char const*) ; 

const char *js_utfidxtoptr(const char *s, int i)
{
	Rune rune;
	while (i-- > 0) {
		rune = *(unsigned char*)s;
		if (rune < Runeself) {
			if (rune == 0)
				return NULL;
			++s;
		} else
			s += chartorune(&rune, s);
	}
	return s;
}