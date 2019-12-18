#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct line {int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_2__ {float lineheight; } ;

/* Variables and functions */
 char* find_string_location (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float) ; 
 TYPE_1__ ui ; 

__attribute__((used)) static char *find_input_location(struct line *lines, int n, float left, float top, float x, float y)
{
	int i = 0;
	if (y > top) i = (y - top) / ui.lineheight;
	if (i >= n) i = n - 1;
	return find_string_location(lines[i].a, lines[i].b, left, x);
}