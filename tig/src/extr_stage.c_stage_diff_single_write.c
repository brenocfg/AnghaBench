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
struct line {int type; } ;
struct io {int dummy; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 int LINE_DIFF_ADD ; 
 int LINE_DIFF_DEL ; 
 char* box_text (struct line*) ; 
 int /*<<< orphan*/  io_printf (struct io*,char*,char const*,char const*) ; 
 scalar_t__ stage_diff_done (struct line*,struct line*) ; 

__attribute__((used)) static bool
stage_diff_single_write(struct io *io, bool staged,
			struct line *line, struct line *single, struct line *end)
{
	enum line_type write_as_normal = staged ? LINE_DIFF_ADD : LINE_DIFF_DEL;
	enum line_type ignore = staged ? LINE_DIFF_DEL : LINE_DIFF_ADD;

	while (line < end) {
		const char *prefix = "";
		const char *data = box_text(line);

		if (line == single) {
			/* Write the complete line. */

		} else if (line->type == write_as_normal) {
			prefix = " ";
			data = data + 1;

		} else if (line->type == ignore) {
			data = NULL;
		}

		if (data && !io_printf(io, "%s%s\n", prefix, data))
			return false;

		line++;
		if (stage_diff_done(line, end))
			break;
	}

	return true;
}