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
struct TYPE_2__ {int* nesting_bounds; int current_level; int level_offset; } ;
struct html_renderopt {int flags; TYPE_1__ toc_data; } ;
struct buf {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 
 int HTML_ESCAPE ; 
 int /*<<< orphan*/  bufprintf (struct buf*,char*) ; 
 int /*<<< orphan*/  bufput (struct buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  escape_html (struct buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndr_header_anchor (struct buf*,struct buf const*) ; 

__attribute__((used)) static void
toc_header(struct buf *ob, const struct buf *text, int level, void *opaque)
{
	struct html_renderopt *options = opaque;

	if (level >= options->toc_data.nesting_bounds[0] &&
	    level <= options->toc_data.nesting_bounds[1]) {
		/* set the level offset if this is the first header
		 * we're parsing for the document */
		if (options->toc_data.current_level == 0)
			options->toc_data.level_offset = level - 1;

		level -= options->toc_data.level_offset;

		if (level > options->toc_data.current_level) {
			while (level > options->toc_data.current_level) {
				BUFPUTSL(ob, "<ul>\n<li>\n");
				options->toc_data.current_level++;
			}
		} else if (level < options->toc_data.current_level) {
			BUFPUTSL(ob, "</li>\n");
			while (level < options->toc_data.current_level) {
				BUFPUTSL(ob, "</ul>\n</li>\n");
				options->toc_data.current_level--;
			}
			BUFPUTSL(ob,"<li>\n");
		} else {
			BUFPUTSL(ob,"</li>\n<li>\n");
		}

		bufprintf(ob, "<a href=\"#");
		rndr_header_anchor(ob, text);
		BUFPUTSL(ob, "\">");

		if (text) {
			if (options->flags & HTML_ESCAPE)
				escape_html(ob, text->data, text->size);
			else
				bufput(ob, text->data, text->size);
		}

		BUFPUTSL(ob, "</a>\n");
	}
}