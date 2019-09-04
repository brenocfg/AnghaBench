#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct view {TYPE_2__* ops; } ;
struct line {struct box* data; } ;
struct box {size_t cells; TYPE_1__* cell; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;
struct TYPE_4__ {scalar_t__ column_bits; } ;
struct TYPE_3__ {size_t length; int type; } ;

/* Variables and functions */
 struct line* add_line_at (struct view*,unsigned long,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  box_sizeof (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  box_text_copy (struct box*,size_t,char const*,size_t) ; 
 int /*<<< orphan*/  view_column_info_update (struct view*,struct line*) ; 

struct line *
add_line_text_at_(struct view *view, unsigned long pos, const char *text, size_t textlen, enum line_type type, size_t cells, bool custom)
{
	struct box *box;
	struct line *line = add_line_at(view, pos, NULL, type, box_sizeof(NULL, cells, textlen), custom);

	if (!line)
		return NULL;

	box = line->data;
	box->cell[box->cells].length = textlen;
	box->cell[box->cells++].type = type;
	box_text_copy(box, cells, text, textlen);

	if (view->ops->column_bits)
		view_column_info_update(view, line);
	return line;
}