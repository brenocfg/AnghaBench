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
struct buf {size_t size; char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 
 int /*<<< orphan*/  bufprintf (struct buf*,char*,unsigned int) ; 
 int /*<<< orphan*/  bufput (struct buf*,char*,size_t) ; 

__attribute__((used)) static void
rndr_footnote_def(struct buf *ob, const struct buf *text, unsigned int num, void *opaque)
{
	size_t i = 0;
	int pfound = 0;

	/* insert anchor at the end of first paragraph block */
	if (text) {
		while ((i+3) < text->size) {
			if (text->data[i++] != '<') continue;
			if (text->data[i++] != '/') continue;
			if (text->data[i++] != 'p' && text->data[i] != 'P') continue;
			if (text->data[i] != '>') continue;
			i -= 3;
			pfound = 1;
			break;
		}
	}

	bufprintf(ob, "\n<li id=\"fn%d\">\n", num);
	if (pfound) {
		bufput(ob, text->data, i);
		bufprintf(ob, "&nbsp;<a href=\"#fnref%d\">&#8617;</a>", num);
		bufput(ob, text->data + i, text->size - i);
	} else if (text) {
		bufput(ob, text->data, text->size);
	}
	BUFPUTSL(ob, "</li>\n");
}