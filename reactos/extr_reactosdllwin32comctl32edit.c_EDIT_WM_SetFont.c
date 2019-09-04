#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int style; int flags; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  selection_end; int /*<<< orphan*/  line_height; int /*<<< orphan*/  char_width; int /*<<< orphan*/  font; } ;
struct TYPE_13__ {int /*<<< orphan*/  tmAveCharWidth; int /*<<< orphan*/  tmHeight; } ;
typedef  TYPE_1__ TEXTMETRICW ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_2__ EDITSTATE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCaret (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyCaret () ; 
 int EC_LEFTMARGIN ; 
 int EC_RIGHTMARGIN ; 
 int /*<<< orphan*/  EC_USEFONTINFO ; 
 int /*<<< orphan*/  EDIT_BuildLineDefs_ML (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_CalcLineWidth_SL (TYPE_2__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetMargins (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_InvalidateUniscribeData (TYPE_2__*) ; 
 int /*<<< orphan*/  EDIT_SetCaretPos (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDIT_SetRectNP (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_UpdateText (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EF_AFTER_WRAP ; 
 int EF_FOCUSED ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextMetricsW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowCaret (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_text_length (TYPE_2__*) ; 

__attribute__((used)) static void EDIT_WM_SetFont(EDITSTATE *es, HFONT font, BOOL redraw)
{
	TEXTMETRICW tm;
	HDC dc;
	HFONT old_font = 0;
	RECT clientRect;

	es->font = font;
	EDIT_InvalidateUniscribeData(es);
	dc = GetDC(es->hwndSelf);
	if (font)
		old_font = SelectObject(dc, font);
	GetTextMetricsW(dc, &tm);
	es->line_height = tm.tmHeight;
	es->char_width = tm.tmAveCharWidth;
	if (font)
		SelectObject(dc, old_font);
	ReleaseDC(es->hwndSelf, dc);

	/* Reset the format rect and the margins */
	GetClientRect(es->hwndSelf, &clientRect);
	EDIT_SetRectNP(es, &clientRect);
	EDIT_EM_SetMargins(es, EC_LEFTMARGIN | EC_RIGHTMARGIN,
			   EC_USEFONTINFO, EC_USEFONTINFO, FALSE);

	if (es->style & ES_MULTILINE)
		EDIT_BuildLineDefs_ML(es, 0, get_text_length(es), 0, NULL);
	else
	    EDIT_CalcLineWidth_SL(es);

	if (redraw)
		EDIT_UpdateText(es, NULL, TRUE);
	if (es->flags & EF_FOCUSED) {
		DestroyCaret();
		CreateCaret(es->hwndSelf, 0, 1, es->line_height);
		EDIT_SetCaretPos(es, es->selection_end,
				 es->flags & EF_AFTER_WRAP);
		ShowCaret(es->hwndSelf);
	}
}