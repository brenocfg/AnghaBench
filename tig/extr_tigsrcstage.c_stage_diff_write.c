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
struct line {int dummy; } ;
struct io {int dummy; } ;

/* Variables and functions */
 char* box_text (struct line*) ; 
 int /*<<< orphan*/  io_write (struct io*,char const*,int) ; 
 scalar_t__ stage_diff_done (struct line*,struct line*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool
stage_diff_write(struct io *io, struct line *line, struct line *end)
{
	while (line < end) {
		const char *text = box_text(line);

		if (!io_write(io, text, strlen(text)) ||
		    !io_write(io, "\n", 1))
			return false;
		line++;
		if (stage_diff_done(line, end))
			break;
	}

	return true;
}