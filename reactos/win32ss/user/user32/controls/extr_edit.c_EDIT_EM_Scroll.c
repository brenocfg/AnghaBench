#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bottom; int top; } ;
struct TYPE_7__ {int style; int y_offset; int line_count; int line_height; TYPE_1__ format_rect; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int INT ;
typedef  TYPE_2__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_LineScroll (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAKELONG (int,int /*<<< orphan*/ ) ; 
#define  SB_LINEDOWN 131 
#define  SB_LINEUP 130 
#define  SB_PAGEDOWN 129 
#define  SB_PAGEUP 128 
 int /*<<< orphan*/  TRUE ; 
 int get_vertical_line_count (TYPE_2__*) ; 
 int max (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT EDIT_EM_Scroll(EDITSTATE *es, INT action)
{
	INT dy;

	if (!(es->style & ES_MULTILINE))
		return (LRESULT)FALSE;

	dy = 0;

	switch (action) {
	case SB_LINEUP:
		if (es->y_offset)
			dy = -1;
		break;
	case SB_LINEDOWN:
		if (es->y_offset < es->line_count - 1)
			dy = 1;
		break;
	case SB_PAGEUP:
		if (es->y_offset)
			dy = -(es->format_rect.bottom - es->format_rect.top) / es->line_height;
		break;
	case SB_PAGEDOWN:
		if (es->y_offset < es->line_count - 1)
			dy = (es->format_rect.bottom - es->format_rect.top) / es->line_height;
		break;
	default:
		return (LRESULT)FALSE;
	}
	if (dy) {
	    INT vlc = get_vertical_line_count(es);
	    /* check if we are going to move too far */
	    if(es->y_offset + dy > es->line_count - vlc)
		dy = max(es->line_count - vlc, 0) - es->y_offset;

	    /* Notification is done in EDIT_EM_LineScroll */
	    if(dy) {
		EDIT_EM_LineScroll(es, 0, dy);
		return MAKELONG(dy, TRUE);
	    }

	}
	return (LRESULT)FALSE;
}