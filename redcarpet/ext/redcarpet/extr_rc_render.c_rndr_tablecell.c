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
struct buf {int dummy; } ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_CALLBACK (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSTR2SYM (char*) ; 
#define  MKD_TABLE_ALIGN_CENTER 130 
#define  MKD_TABLE_ALIGN_L 129 
#define  MKD_TABLE_ALIGN_R 128 
 int /*<<< orphan*/  Qnil ; 
 int /*<<< orphan*/  buf2str (struct buf const*) ; 

__attribute__((used)) static void
rndr_tablecell(struct buf *ob, const struct buf *text, int align, void *opaque)
{
	VALUE rb_align;

	switch (align) {
	case MKD_TABLE_ALIGN_L:
		rb_align = CSTR2SYM("left");
		break;

	case MKD_TABLE_ALIGN_R:
		rb_align = CSTR2SYM("right");
		break;

	case MKD_TABLE_ALIGN_CENTER:
		rb_align = CSTR2SYM("center");
		break;

	default:
		rb_align = Qnil;
		break;
	}

	BLOCK_CALLBACK("table_cell", 2, buf2str(text), rb_align);
}