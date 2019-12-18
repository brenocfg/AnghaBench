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
struct TYPE_4__ {int /*<<< orphan*/  (* footnotes ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_2__ cb; } ;
struct footnote_ref {TYPE_1__* contents; int /*<<< orphan*/  num; } ;
struct footnote_list {scalar_t__ count; struct footnote_item* head; } ;
struct footnote_item {struct footnote_item* next; struct footnote_ref* ref; } ;
struct buf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_BLOCK ; 
 int /*<<< orphan*/  parse_footnote_def (struct buf*,struct sd_markdown*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buf* rndr_newbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndr_popbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_footnote_list(struct buf *ob, struct sd_markdown *rndr, struct footnote_list *footnotes)
{
	struct buf *work = 0;
	struct footnote_item *item;
	struct footnote_ref *ref;

	if (footnotes->count == 0)
		return;

	work = rndr_newbuf(rndr, BUFFER_BLOCK);

	item = footnotes->head;
	while (item) {
		ref = item->ref;
		parse_footnote_def(work, rndr, ref->num, ref->contents->data, ref->contents->size);
		item = item->next;
	}

	if (rndr->cb.footnotes)
		rndr->cb.footnotes(ob, work, rndr->opaque);
	rndr_popbuf(rndr, BUFFER_BLOCK);
}