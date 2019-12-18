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
 int /*<<< orphan*/  fz_chartorune (int*,char const*) ; 
 scalar_t__ ui_measure_character (int) ; 

float ui_measure_string_part(const char *s, const char *e)
{
	int c;
	float w = 0;
	while (s < e)
	{
		s += fz_chartorune(&c, s);
		w += ui_measure_character(c);
	}
	return w;
}