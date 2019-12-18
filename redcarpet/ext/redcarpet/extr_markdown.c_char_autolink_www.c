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
struct TYPE_2__ {int /*<<< orphan*/  (* link ) (struct buf*,struct buf*,int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* normal_text ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; scalar_t__ in_link_body; } ;
struct buf {size_t size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_SPAN ; 
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 
 int /*<<< orphan*/  bufput (struct buf*,int /*<<< orphan*/ ,size_t) ; 
 struct buf* rndr_newbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndr_popbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 size_t sd_autolink__www (size_t*,struct buf*,int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct buf*,struct buf*,int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct buf*,struct buf*,int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
char_autolink_www(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t offset, size_t size)
{
	struct buf *link, *link_url, *link_text;
	size_t link_len, rewind;

	if (!rndr->cb.link || rndr->in_link_body)
		return 0;

	link = rndr_newbuf(rndr, BUFFER_SPAN);

	if ((link_len = sd_autolink__www(&rewind, link, data, offset, size, 0)) > 0) {
		link_url = rndr_newbuf(rndr, BUFFER_SPAN);
		BUFPUTSL(link_url, "http://");
		bufput(link_url, link->data, link->size);

		ob->size -= rewind;
		if (rndr->cb.normal_text) {
			link_text = rndr_newbuf(rndr, BUFFER_SPAN);
			rndr->cb.normal_text(link_text, link, rndr->opaque);
			rndr->cb.link(ob, link_url, NULL, link_text, rndr->opaque);
			rndr_popbuf(rndr, BUFFER_SPAN);
		} else {
			rndr->cb.link(ob, link_url, NULL, link, rndr->opaque);
		}
		rndr_popbuf(rndr, BUFFER_SPAN);
	}

	rndr_popbuf(rndr, BUFFER_SPAN);
	return link_len;
}