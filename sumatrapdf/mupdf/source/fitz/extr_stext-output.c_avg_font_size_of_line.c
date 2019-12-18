#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* next; scalar_t__ size; } ;
typedef  TYPE_1__ fz_stext_char ;

/* Variables and functions */

__attribute__((used)) static float avg_font_size_of_line(fz_stext_char *ch)
{
	float size = 0;
	int n = 0;
	if (!ch)
		return 0;
	while (ch)
	{
		size += ch->size;
		++n;
		ch = ch->next;
	}
	return size / n;
}