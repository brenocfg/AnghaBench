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
typedef  scalar_t__ u_int ;
struct tty {int flags; } ;
struct TYPE_2__ {int size; int* data; scalar_t__ width; } ;
typedef  struct grid_cell {TYPE_1__ data; } const grid_cell ;

/* Variables and functions */
 int TTY_UTF8 ; 
 scalar_t__ UTF8_SIZE ; 
 int /*<<< orphan*/  memcpy (struct grid_cell const*,struct grid_cell const*,int) ; 
 int /*<<< orphan*/  memset (int*,char,scalar_t__) ; 

__attribute__((used)) static const struct grid_cell *
tty_check_codeset(struct tty *tty, const struct grid_cell *gc)
{
	static struct grid_cell	new;
	u_int			n;

	/* Characters less than 0x7f are always fine, no matter what. */
	if (gc->data.size == 1 && *gc->data.data < 0x7f)
		return (gc);

	/* UTF-8 terminal and a UTF-8 character - fine. */
	if (tty->flags & TTY_UTF8)
		return (gc);

	/* Replace by the right number of underscores. */
	n = gc->data.width;
	if (n > UTF8_SIZE)
		n = UTF8_SIZE;
	memcpy(&new, gc, sizeof new);
	new.data.size = n;
	memset(new.data.data, '_', n);
	return (&new);
}