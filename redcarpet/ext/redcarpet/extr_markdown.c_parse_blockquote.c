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
struct TYPE_2__ {int /*<<< orphan*/  (* blockquote ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_BLOCK ; 
 scalar_t__ is_empty (char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  parse_block (struct buf*,struct sd_markdown*,char*,size_t) ; 
 size_t prefix_quote (char*,size_t) ; 
 struct buf* rndr_newbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndr_popbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
parse_blockquote(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
	size_t beg, end = 0, pre, work_size = 0;
	uint8_t *work_data = 0;
	struct buf *out = 0;

	out = rndr_newbuf(rndr, BUFFER_BLOCK);
	beg = 0;
	while (beg < size) {
		for (end = beg + 1; end < size && data[end - 1] != '\n'; end++);

		pre = prefix_quote(data + beg, end - beg);

		if (pre)
			beg += pre; /* skipping prefix */

		/* empty line followed by non-quote line */
		else if (is_empty(data + beg, end - beg) &&
				(end >= size || (prefix_quote(data + end, size - end) == 0 &&
				!is_empty(data + end, size - end))))
			break;

		if (beg < end) { /* copy into the in-place working buffer */
			/* bufput(work, data + beg, end - beg); */
			if (!work_data)
				work_data = data + beg;
			else if (data + beg != work_data + work_size)
				memmove(work_data + work_size, data + beg, end - beg);
			work_size += end - beg;
		}
		beg = end;
	}

	parse_block(out, rndr, work_data, work_size);
	if (rndr->cb.blockquote)
		rndr->cb.blockquote(ob, out, rndr->opaque);
	rndr_popbuf(rndr, BUFFER_BLOCK);
	return end;
}