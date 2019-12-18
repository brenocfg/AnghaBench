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
struct buf {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 
 int MKD_TABLE_ALIGNMASK ; 
#define  MKD_TABLE_ALIGN_CENTER 130 
#define  MKD_TABLE_ALIGN_L 129 
#define  MKD_TABLE_ALIGN_R 128 
 int MKD_TABLE_HEADER ; 
 int /*<<< orphan*/  bufput (struct buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rndr_tablecell(struct buf *ob, const struct buf *text, int flags, void *opaque)
{
	if (flags & MKD_TABLE_HEADER) {
		BUFPUTSL(ob, "<th");
	} else {
		BUFPUTSL(ob, "<td");
	}

	switch (flags & MKD_TABLE_ALIGNMASK) {
	case MKD_TABLE_ALIGN_CENTER:
		BUFPUTSL(ob, " style=\"text-align: center\">");
		break;

	case MKD_TABLE_ALIGN_L:
		BUFPUTSL(ob, " style=\"text-align: left\">");
		break;

	case MKD_TABLE_ALIGN_R:
		BUFPUTSL(ob, " style=\"text-align: right\">");
		break;

	default:
		BUFPUTSL(ob, ">");
	}

	if (text)
		bufput(ob, text->data, text->size);

	if (flags & MKD_TABLE_HEADER) {
		BUFPUTSL(ob, "</th>\n");
	} else {
		BUFPUTSL(ob, "</td>\n");
	}
}