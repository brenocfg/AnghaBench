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
 int find_changing (unsigned char const*,int,int) ; 
 int getbit (unsigned char const*,int) ; 

__attribute__((used)) static inline int
find_changing_color(const unsigned char *line, int x, int w, int color)
{
	if (!line || x >= w)
		return w;

	x = find_changing(line, (x > 0 || !color) ? x : -1, w);

	if (x < w && getbit(line, x) != color)
		x = find_changing(line, x, w);

	return x;
}