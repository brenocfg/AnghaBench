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
 int /*<<< orphan*/  bufput (struct buf*,char*,size_t) ; 

__attribute__((used)) static void
rndr_listitem(struct buf *ob, const struct buf *text, int flags, void *opaque)
{
	BUFPUTSL(ob, "<li>");
	if (text) {
		size_t size = text->size;
		while (size && text->data[size - 1] == '\n')
			size--;

		bufput(ob, text->data, size);
	}
	BUFPUTSL(ob, "</li>\n");
}