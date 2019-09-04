#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct line {scalar_t__ type; } ;
struct io {int dummy; } ;
struct TYPE_4__ {scalar_t__ lines; int /*<<< orphan*/  position; } ;
struct TYPE_3__ {scalar_t__ lines; int /*<<< orphan*/  position; } ;
struct chunk_header {TYPE_2__ new; TYPE_1__ old; } ;

/* Variables and functions */
 scalar_t__ LINE_DIFF_DEL ; 
 scalar_t__ LINE_STAT_STAGED ; 
 int /*<<< orphan*/  box_text (struct line*) ; 
 scalar_t__ io_printf (struct io*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  parse_chunk_header (struct chunk_header*,int /*<<< orphan*/ ) ; 
 scalar_t__ stage_diff_single_write (struct io*,int,struct line*,struct line*,struct line*) ; 
 scalar_t__ stage_diff_write (struct io*,struct line*,struct line*) ; 
 scalar_t__ stage_line_type ; 

__attribute__((used)) static bool
stage_apply_line(struct io *io, struct line *diff_hdr, struct line *chunk, struct line *single, struct line *end)
{
	struct chunk_header header;
	bool staged = stage_line_type == LINE_STAT_STAGED;
	int diff = single->type == LINE_DIFF_DEL ? -1 : 1;

	if (!parse_chunk_header(&header, box_text(chunk)))
		return false;

	if (staged)
		header.old.lines = header.new.lines - diff;
	else
		header.new.lines = header.old.lines + diff;

	return stage_diff_write(io, diff_hdr, chunk) &&
	       io_printf(io, "@@ -%lu,%lu +%lu,%lu @@\n",
		       header.old.position, header.old.lines,
		       header.new.position, header.new.lines) &&
	       stage_diff_single_write(io, staged, chunk + 1, single, end);
}