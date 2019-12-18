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
 unsigned char Runeself ; 
 int /*<<< orphan*/  chartorune (int /*<<< orphan*/ *,char const*) ; 

int js_utfptrtoidx(const char *s, const char *p)
{
	Rune rune;
	int i = 0;
	while (s < p) {
		if (*(unsigned char *)s < Runeself)
			++s;
		else
			s += chartorune(&rune, s);
		++i;
	}
	return i;
}