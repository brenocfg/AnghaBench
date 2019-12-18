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
typedef  int u_int ;
struct screen {int /*<<< orphan*/ * tabs; } ;

/* Variables and functions */
 int /*<<< orphan*/ * bit_alloc (int) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int screen_size_x (struct screen*) ; 

void
screen_reset_tabs(struct screen *s)
{
	u_int	i;

	free(s->tabs);

	if ((s->tabs = bit_alloc(screen_size_x(s))) == NULL)
		fatal("bit_alloc failed");
	for (i = 8; i < screen_size_x(s); i += 8)
		bit_set(s->tabs, i);
}