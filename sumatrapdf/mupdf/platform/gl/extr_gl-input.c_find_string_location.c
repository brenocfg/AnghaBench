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
 int fz_chartorune (int*,char*) ; 
 float ui_measure_character (int) ; 

__attribute__((used)) static char *find_string_location(char *s, char *e, float w, float x)
{
	int c;
	while (s < e)
	{
		int n = fz_chartorune(&c, s);
		float cw = ui_measure_character(c);
		if (w + (cw / 2) >= x)
			return s;
		w += cw;
		s += n;
	}
	return e;
}