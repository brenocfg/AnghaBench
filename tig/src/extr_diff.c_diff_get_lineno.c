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
struct view {int dummy; } ;
typedef  struct line {scalar_t__ type; } const line ;
struct TYPE_2__ {unsigned int position; } ;
struct chunk_header {TYPE_1__ new; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DIFF_CHUNK ; 
 scalar_t__ LINE_DIFF_DEL ; 
 scalar_t__ LINE_DIFF_DEL2 ; 
 int /*<<< orphan*/  LINE_DIFF_HEADER ; 
 int /*<<< orphan*/  box_text (struct line const*) ; 
 struct line const* find_prev_line_by_type (struct view*,struct line const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_chunk_header (struct chunk_header*,int /*<<< orphan*/ ) ; 

unsigned int
diff_get_lineno(struct view *view, struct line *line)
{
	const struct line *header, *chunk;
	unsigned int lineno;
	struct chunk_header chunk_header;

	/* Verify that we are after a diff header and one of its chunks */
	header = find_prev_line_by_type(view, line, LINE_DIFF_HEADER);
	chunk = find_prev_line_by_type(view, line, LINE_DIFF_CHUNK);
	if (!header || !chunk || chunk < header)
		return 0;

	/*
	 * In a chunk header, the number after the '+' sign is the number of its
	 * following line, in the new version of the file. We increment this
	 * number for each non-deletion line, until the given line position.
	 */
	if (!parse_chunk_header(&chunk_header, box_text(chunk)))
		return 0;

	lineno = chunk_header.new.position;

	for (chunk++; chunk < line; chunk++)
		if (chunk->type != LINE_DIFF_DEL &&
		    chunk->type != LINE_DIFF_DEL2)
			lineno++;

	return lineno;
}