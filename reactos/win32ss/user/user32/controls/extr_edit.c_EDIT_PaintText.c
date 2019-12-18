#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ left; } ;
struct TYPE_13__ {scalar_t__ composition_len; int style; scalar_t__ text; scalar_t__ x_offset; TYPE_1__ format_rect; int /*<<< orphan*/  tabs; int /*<<< orphan*/  tabs_count; } ;
struct TYPE_12__ {int /*<<< orphan*/  lfUnderline; } ;
struct TYPE_11__ {scalar_t__ cx; } ;
typedef  TYPE_2__ SIZE ;
typedef  TYPE_3__ LOGFONTW ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_4__ EDITSTATE ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_HIGHLIGHT ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHTTEXT ; 
 scalar_t__ CreateFontIndirectW (TYPE_3__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 scalar_t__ EDIT_EM_LineIndex (TYPE_4__*,scalar_t__) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  GetBkColor (int /*<<< orphan*/ ) ; 
 scalar_t__ GetBkMode (int /*<<< orphan*/ ) ; 
 scalar_t__ GetCurrentObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetObjectW (scalar_t__,int,TYPE_3__*) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,scalar_t__,scalar_t__,TYPE_2__*) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_FONT ; 
 scalar_t__ OPAQUE ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkMode (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TabbedTextOutW (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TextOutW (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static INT EDIT_PaintText(EDITSTATE *es, HDC dc, INT x, INT y, INT line, INT col, INT count, BOOL rev)
{
	COLORREF BkColor;
	COLORREF TextColor;
	LOGFONTW underline_font;
	HFONT hUnderline = 0;
	HFONT old_font = 0;
	INT ret;
	INT li;
	INT BkMode;
	SIZE size;

	if (!count)
		return 0;
	BkMode = GetBkMode(dc);
	BkColor = GetBkColor(dc);
	TextColor = GetTextColor(dc);
	if (rev) {
	        if (es->composition_len == 0)
	        {
			SetBkColor(dc, GetSysColor(COLOR_HIGHLIGHT));
			SetTextColor(dc, GetSysColor(COLOR_HIGHLIGHTTEXT));
			SetBkMode( dc, OPAQUE);
	        }
		else
		{
			HFONT current = GetCurrentObject(dc,OBJ_FONT);
			GetObjectW(current,sizeof(LOGFONTW),&underline_font);
			underline_font.lfUnderline = TRUE;
	            	hUnderline = CreateFontIndirectW(&underline_font);
			old_font = SelectObject(dc,hUnderline);
	        }
	}
	li = EDIT_EM_LineIndex(es, line);
	if (es->style & ES_MULTILINE) {
		ret = (INT)LOWORD(TabbedTextOutW(dc, x, y, es->text + li + col, count,
					es->tabs_count, es->tabs, es->format_rect.left - es->x_offset));
	} else {
		TextOutW(dc, x, y, es->text + li + col, count);
		GetTextExtentPoint32W(dc, es->text + li + col, count, &size);
		ret = size.cx;
	}
	if (rev) {
		if (es->composition_len == 0)
		{
			SetBkColor(dc, BkColor);
			SetTextColor(dc, TextColor);
			SetBkMode( dc, BkMode);
		}
		else
		{
			if (old_font)
				SelectObject(dc,old_font);
			if (hUnderline)
				DeleteObject(hUnderline);
	        }
	}
	return ret;
}