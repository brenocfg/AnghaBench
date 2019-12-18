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
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 
 int HTML_PRETTIFY ; 
 int /*<<< orphan*/  escape_html (struct buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rndr_codespan(struct buf *ob, const struct buf *text, void *opaque)
{
	struct html_renderopt *options = opaque;
	if (options->flags & HTML_PRETTIFY)
		BUFPUTSL(ob, "<code class=\"prettyprint\">");
	else
		BUFPUTSL(ob, "<code>");
	if (text) escape_html(ob, text->data, text->size);
	BUFPUTSL(ob, "</code>");
	return 1;
}