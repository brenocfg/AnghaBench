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
struct html_renderopt {int flags; int /*<<< orphan*/  (* link_attributes ) (struct buf*,struct buf const*,void*) ;} ;
struct buf {scalar_t__ size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 
 int HTML_SAFELINK ; 
 int /*<<< orphan*/  bufput (struct buf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bufputc (struct buf*,char) ; 
 int /*<<< orphan*/  escape_href (struct buf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  escape_html (struct buf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sd_autolink_issafe (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf const*,void*) ; 

__attribute__((used)) static int
rndr_link(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *content, void *opaque)
{
	struct html_renderopt *options = opaque;

	if (link != NULL && (options->flags & HTML_SAFELINK) != 0 && !sd_autolink_issafe(link->data, link->size))
		return 0;

	BUFPUTSL(ob, "<a href=\"");

	if (link && link->size)
		escape_href(ob, link->data, link->size);

	if (title && title->size) {
		BUFPUTSL(ob, "\" title=\"");
		escape_html(ob, title->data, title->size);
	}

	if (options->link_attributes) {
		bufputc(ob, '\"');
		options->link_attributes(ob, link, opaque);
		bufputc(ob, '>');
	} else {
		BUFPUTSL(ob, "\">");
	}

	if (content && content->size) bufput(ob, content->data, content->size);
	BUFPUTSL(ob, "</a>");
	return 1;
}