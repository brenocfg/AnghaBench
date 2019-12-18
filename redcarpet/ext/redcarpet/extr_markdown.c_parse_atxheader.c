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
typedef  char uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* header ) (struct buf*,struct buf*,int,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_SPAN ; 
 int /*<<< orphan*/  parse_inline (struct buf*,struct sd_markdown*,char*,size_t) ; 
 struct buf* rndr_newbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndr_popbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
parse_atxheader(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
	size_t level = 0;
	size_t i, end, skip;

	while (level < size && level < 6 && data[level] == '#')
		level++;

	for (i = level; i < size && data[i] == ' '; i++);

	for (end = i; end < size && data[end] != '\n'; end++);
	skip = end;

	while (end && data[end - 1] == '#')
		end--;

	while (end && data[end - 1] == ' ')
		end--;

	if (end > i) {
		struct buf *work = rndr_newbuf(rndr, BUFFER_SPAN);

		parse_inline(work, rndr, data + i, end - i);

		if (rndr->cb.header)
			rndr->cb.header(ob, work, (int)level, rndr->opaque);

		rndr_popbuf(rndr, BUFFER_SPAN);
	}

	return skip;
}