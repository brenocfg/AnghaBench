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
struct screen {int /*<<< orphan*/  ccolour; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void
screen_set_cursor_colour(struct screen *s, const char *colour)
{
	free(s->ccolour);
	s->ccolour = xstrdup(colour);
}