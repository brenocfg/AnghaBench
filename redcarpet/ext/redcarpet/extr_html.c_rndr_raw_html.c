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
struct buf {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int HTML_ESCAPE ; 
 int HTML_SKIP_HTML ; 
 int HTML_SKIP_IMAGES ; 
 int HTML_SKIP_LINKS ; 
 int HTML_SKIP_STYLE ; 
 int /*<<< orphan*/  bufput (struct buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  escape_html (struct buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sdhtml_is_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
rndr_raw_html(struct buf *ob, const struct buf *text, void *opaque)
{
	struct html_renderopt *options = opaque;

	/* HTML_ESCAPE overrides SKIP_HTML, SKIP_STYLE, SKIP_LINKS and SKIP_IMAGES
	   It doesn't see if there are any valid tags, just escape all of them. */
	if((options->flags & HTML_ESCAPE) != 0) {
		escape_html(ob, text->data, text->size);
		return 1;
	}

	if ((options->flags & HTML_SKIP_HTML) != 0)
		return 1;

	if ((options->flags & HTML_SKIP_STYLE) != 0 &&
		sdhtml_is_tag(text->data, text->size, "style"))
		return 1;

	if ((options->flags & HTML_SKIP_LINKS) != 0 &&
		sdhtml_is_tag(text->data, text->size, "a"))
		return 1;

	if ((options->flags & HTML_SKIP_IMAGES) != 0 &&
		sdhtml_is_tag(text->data, text->size, "img"))
		return 1;

	bufput(ob, text->data, text->size);
	return 1;
}