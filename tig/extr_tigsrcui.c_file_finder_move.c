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
struct TYPE_2__ {int lineno; int offset; } ;
struct file_finder {int lines; int height; TYPE_1__ pos; } ;

/* Variables and functions */

__attribute__((used)) static void
file_finder_move(struct file_finder *finder, int direction)
{
	if (direction < 0 && finder->pos.lineno <= -direction)
		finder->pos.lineno = 0;
	else
		finder->pos.lineno += direction;

	if (finder->pos.lineno >= finder->lines) {
		if (finder->lines > 0)
			finder->pos.lineno = finder->lines - 1;
		else
			finder->pos.lineno = 0;
        }

	if (finder->pos.offset + finder->height <= finder->pos.lineno)
		finder->pos.offset = finder->pos.lineno - (finder->height / 2);

	if (finder->pos.offset > finder->pos.lineno)
		finder->pos.offset = finder->pos.lineno;

	if (finder->lines <= finder->height)
		finder->pos.offset = 0;
}