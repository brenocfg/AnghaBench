#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ right; scalar_t__ left; scalar_t__ bottom; scalar_t__ top; } ;
struct TYPE_13__ {scalar_t__ char_width; int style; scalar_t__ line_height; scalar_t__ text_width; scalar_t__ x_offset; scalar_t__ line_count; scalar_t__ y_offset; int flags; int /*<<< orphan*/  selection_end; TYPE_1__ format_rect; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_12__ {int /*<<< orphan*/  bottom; } ;
typedef  TYPE_2__ RECT ;
typedef  scalar_t__ INT ;
typedef  TYPE_3__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_BuildLineDefs_ML (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_SetCaretPos (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDIT_UpdateScrollInfo (TYPE_3__*) ; 
 int EF_AFTER_WRAP ; 
 int ES_AUTOHSCROLL ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  get_text_length (TYPE_3__*) ; 
 scalar_t__ get_vertical_line_count (TYPE_3__*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EDIT_AdjustFormatRect(EDITSTATE *es)
{
	RECT ClientRect;

	es->format_rect.right = max(es->format_rect.right, es->format_rect.left + es->char_width);
	if (es->style & ES_MULTILINE)
	{
	    INT fw, vlc, max_x_offset, max_y_offset;

	    vlc = get_vertical_line_count(es);
	    es->format_rect.bottom = es->format_rect.top + vlc * es->line_height;

	    /* correct es->x_offset */
	    fw = es->format_rect.right - es->format_rect.left;
	    max_x_offset = es->text_width - fw;
	    if(max_x_offset < 0) max_x_offset = 0;
	    if(es->x_offset > max_x_offset)
		es->x_offset = max_x_offset;

	    /* correct es->y_offset */
	    max_y_offset = es->line_count - vlc;
	    if(max_y_offset < 0) max_y_offset = 0;
	    if(es->y_offset > max_y_offset)
		es->y_offset = max_y_offset;

	    /* force scroll info update */
	    EDIT_UpdateScrollInfo(es);
	}
	else
	/* Windows doesn't care to fix text placement for SL controls */
		es->format_rect.bottom = es->format_rect.top + es->line_height;

	/* Always stay within the client area */
	GetClientRect(es->hwndSelf, &ClientRect);
	es->format_rect.bottom = min(es->format_rect.bottom, ClientRect.bottom);

	if ((es->style & ES_MULTILINE) && !(es->style & ES_AUTOHSCROLL))
		EDIT_BuildLineDefs_ML(es, 0, get_text_length(es), 0, NULL);

	EDIT_SetCaretPos(es, es->selection_end, es->flags & EF_AFTER_WRAP);
}