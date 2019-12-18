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
struct buf {scalar_t__ size; scalar_t__ data; } ;
typedef  enum mkd_autolink { ____Placeholder_mkd_autolink } mkd_autolink ;

/* Variables and functions */
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 
 int HTML_SAFELINK ; 
 int MKDA_EMAIL ; 
 scalar_t__ bufprefix (struct buf const*,char*) ; 
 int /*<<< orphan*/  bufputc (struct buf*,char) ; 
 int /*<<< orphan*/  escape_href (struct buf*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  escape_html (struct buf*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sd_autolink_issafe (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf const*,void*) ; 

__attribute__((used)) static int
rndr_autolink(struct buf *ob, const struct buf *link, enum mkd_autolink type, void *opaque)
{
	struct html_renderopt *options = opaque;

	if (!link || !link->size)
		return 0;

	if ((options->flags & HTML_SAFELINK) != 0 &&
		!sd_autolink_issafe(link->data, link->size) &&
		type != MKDA_EMAIL)
		return 0;

	BUFPUTSL(ob, "<a href=\"");
	if (type == MKDA_EMAIL)
		BUFPUTSL(ob, "mailto:");
	escape_href(ob, link->data, link->size);

	if (options->link_attributes) {
		bufputc(ob, '\"');
		options->link_attributes(ob, link, opaque);
		bufputc(ob, '>');
	} else {
		BUFPUTSL(ob, "\">");
	}

	/*
	 * Pretty printing: if we get an email address as
	 * an actual URI, e.g. `mailto:foo@bar.com`, we don't
	 * want to print the `mailto:` prefix
	 */
	if (bufprefix(link, "mailto:") == 0) {
		escape_html(ob, link->data + 7, link->size - 7);
	} else {
		escape_html(ob, link->data, link->size);
	}

	BUFPUTSL(ob, "</a>");

	return 1;
}