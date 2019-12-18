#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ right; scalar_t__ left; scalar_t__ top; } ;
struct TYPE_14__ {int style; scalar_t__ y_offset; scalar_t__ line_height; scalar_t__ x_offset; int char_width; scalar_t__ text_width; TYPE_1__ format_rect; scalar_t__ ssa; TYPE_3__* first_line_def; } ;
struct TYPE_13__ {scalar_t__ ending; scalar_t__ index; scalar_t__ width; scalar_t__ ssa; struct TYPE_13__* next; } ;
struct TYPE_12__ {scalar_t__ cx; } ;
typedef  TYPE_2__ SIZE ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_3__ LINEDEF ;
typedef  int /*<<< orphan*/  INT16 ;
typedef  scalar_t__ INT ;
typedef  TYPE_4__ EDITSTATE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ EDIT_EM_LineFromChar (TYPE_4__*,scalar_t__) ; 
 scalar_t__ EDIT_EM_LineIndex (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  EDIT_UpdateUniscribeData (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ END_WRAP ; 
 int ES_CENTER ; 
 int ES_MULTILINE ; 
 int ES_RIGHT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScriptStringCPtoX (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_2__* ScriptString_pSize (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ get_text_length (TYPE_4__*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static LRESULT EDIT_EM_PosFromChar(EDITSTATE *es, INT index, BOOL after_wrap)
{
	INT len = get_text_length(es);
	INT l;
	INT li;
	INT x = 0;
	INT y = 0;
	INT w;
	INT lw;
	LINEDEF *line_def;

	index = min(index, len);
	if (es->style & ES_MULTILINE) {
		l = EDIT_EM_LineFromChar(es, index);
		EDIT_UpdateUniscribeData(es, NULL, l);

		y = (l - es->y_offset) * es->line_height;
		li = EDIT_EM_LineIndex(es, l);
		if (after_wrap && (li == index) && l) {
			INT l2 = l - 1;
			line_def = es->first_line_def;
			while (l2) {
				line_def = line_def->next;
				l2--;
			}
			if (line_def->ending == END_WRAP) {
				l--;
				y -= es->line_height;
				li = EDIT_EM_LineIndex(es, l);
			}
		}

		line_def = es->first_line_def;
		while (line_def->index != li)
			line_def = line_def->next;

		lw = line_def->width;
		w = es->format_rect.right - es->format_rect.left;
		if (line_def->ssa)
		{
			ScriptStringCPtoX(line_def->ssa, (index - 1) - li, TRUE, &x);
			x -= es->x_offset;
		}
		else
#ifdef __REACTOS__ /* CORE-15780 */
			x = (lw > 0 ? es->x_offset : x - es->x_offset);
#else
			x = es->x_offset;
#endif

		if (es->style & ES_RIGHT)
			x = w - (lw - x);
		else if (es->style & ES_CENTER)
			x += (w - lw) / 2;
	} else {
		INT xoff = 0;
		INT xi = 0;
		EDIT_UpdateUniscribeData(es, NULL, 0);
		if (es->x_offset)
		{
			if (es->ssa)
			{
				if (es->x_offset >= get_text_length(es))
				{
					int leftover = es->x_offset - get_text_length(es);
					if (es->ssa)
					{
						const SIZE *size;
						size = ScriptString_pSize(es->ssa);
						xoff = size->cx;
					}
					else
						xoff = 0;
					xoff += es->char_width * leftover;
				}
				else
					ScriptStringCPtoX(es->ssa, es->x_offset, FALSE, &xoff);
			}
			else
				xoff = 0;
		}
		if (index)
		{
			if (index >= get_text_length(es))
			{
				if (es->ssa)
				{
					const SIZE *size;
					size = ScriptString_pSize(es->ssa);
					xi = size->cx;
				}
				else
					xi = 0;
			}
			else if (es->ssa)
				ScriptStringCPtoX(es->ssa, index, FALSE, &xi);
			else
				xi = 0;
		}
		x = xi - xoff;

		if (index >= es->x_offset) {
			if (!es->x_offset && (es->style & (ES_RIGHT | ES_CENTER)))
			{
				w = es->format_rect.right - es->format_rect.left;
				if (w > es->text_width)
				{
					if (es->style & ES_RIGHT)
						x += w - es->text_width;
					else if (es->style & ES_CENTER)
						x += (w - es->text_width) / 2;
				}
			}
		}
		y = 0;
	}
	x += es->format_rect.left;
	y += es->format_rect.top;
	return MAKELONG((INT16)x, (INT16)y);
}