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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* list ) (struct buf*,struct buf*,int,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_BLOCK ; 
 int MKD_LI_END ; 
 size_t parse_listitem (struct buf*,struct sd_markdown*,int /*<<< orphan*/ *,size_t,int*) ; 
 struct buf* rndr_newbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndr_popbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
parse_list(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int flags)
{
	struct buf *work = 0;
	size_t i = 0, j;

	work = rndr_newbuf(rndr, BUFFER_BLOCK);

	while (i < size) {
		j = parse_listitem(work, rndr, data + i, size - i, &flags);
		i += j;

		if (!j || (flags & MKD_LI_END))
			break;
	}

	if (rndr->cb.list)
		rndr->cb.list(ob, work, flags, rndr->opaque);
	rndr_popbuf(rndr, BUFFER_BLOCK);
	return i;
}