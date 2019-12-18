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
struct TYPE_2__ {int /*<<< orphan*/  (* blockcode ) (struct buf*,struct buf*,struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {scalar_t__ size; char* data; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_BLOCK ; 
 int /*<<< orphan*/  bufput (struct buf*,char*,size_t) ; 
 int /*<<< orphan*/  bufputc (struct buf*,char) ; 
 size_t is_codefence (char*,size_t,struct buf*) ; 
 scalar_t__ is_empty (char*,size_t) ; 
 struct buf* rndr_newbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndr_popbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf*,struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
parse_fencedcode(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
	size_t beg, end;
	struct buf *work = 0;
	struct buf lang = { 0, 0, 0, 0 };

	beg = is_codefence(data, size, &lang);
	if (beg == 0) return 0;

	work = rndr_newbuf(rndr, BUFFER_BLOCK);

	while (beg < size) {
		size_t fence_end;
		struct buf fence_trail = { 0, 0, 0, 0 };

		fence_end = is_codefence(data + beg, size - beg, &fence_trail);
		if (fence_end != 0 && fence_trail.size == 0) {
			beg += fence_end;
			break;
		}

		for (end = beg + 1; end < size && data[end - 1] != '\n'; end++);

		if (beg < end) {
			/* verbatim copy to the working buffer,
				escaping entities */
			if (is_empty(data + beg, end - beg))
				bufputc(work, '\n');
			else bufput(work, data + beg, end - beg);
		}
		beg = end;
	}

	if (work->size && work->data[work->size - 1] != '\n')
		bufputc(work, '\n');

	if (rndr->cb.blockcode)
		rndr->cb.blockcode(ob, work, lang.size ? &lang : NULL, rndr->opaque);

	rndr_popbuf(rndr, BUFFER_BLOCK);
	return beg;
}