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
struct html_renderopt {int flags; } ;
struct buf {scalar_t__ size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 
 int HTML_SAFELINK ; 
 scalar_t__ USE_XHTML (struct html_renderopt*) ; 
 int /*<<< orphan*/  bufputs (struct buf*,char*) ; 
 int /*<<< orphan*/  escape_href (struct buf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  escape_html (struct buf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sd_autolink_issafe (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
rndr_image(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *alt, void *opaque)
{
	struct html_renderopt *options = opaque;

	if (link != NULL && (options->flags & HTML_SAFELINK) != 0 && !sd_autolink_issafe(link->data, link->size))
		return 0;

	BUFPUTSL(ob, "<img src=\"");

	if (link && link->size)
		escape_href(ob, link->data, link->size);

	BUFPUTSL(ob, "\" alt=\"");

	if (alt && alt->size)
		escape_html(ob, alt->data, alt->size);

	if (title && title->size) {
		BUFPUTSL(ob, "\" title=\"");
		escape_html(ob, title->data, title->size);
	}

	bufputs(ob, USE_XHTML(options) ? "\"/>" : "\">");
	return 1;
}