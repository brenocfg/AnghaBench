#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_13__ ;

/* Type definitions */
struct TYPE_27__ {TYPE_1__* editor; int /*<<< orphan*/  hDC; } ;
struct TYPE_26__ {int len; TYPE_13__* style; } ;
struct TYPE_25__ {scalar_t__ left; scalar_t__ right; } ;
struct TYPE_24__ {int dwEffects; int dwMask; } ;
struct TYPE_23__ {int styleFlags; scalar_t__ bEmulateVersion10; scalar_t__ bHaveFocus; int /*<<< orphan*/  bHideSelection; } ;
struct TYPE_22__ {TYPE_2__ fmt; } ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__ ME_Run ;
typedef  TYPE_5__ ME_Context ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
 int CFE_AUTOBACKCOLOR ; 
 int CFM_BACKCOLOR ; 
 int /*<<< orphan*/ * CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgnIndirect (TYPE_3__*) ; 
 int /*<<< orphan*/  DSTINVERT ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int ES_NOHIDESEL ; 
 int /*<<< orphan*/  ExtSelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int GetClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SelectStyleFont (TYPE_5__*,TYPE_13__*) ; 
 int /*<<< orphan*/  ME_UnselectStyleFont (TYPE_5__*,TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  PatBlt (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGN_AND ; 
 int /*<<< orphan*/  RGN_COPY ; 
 int /*<<< orphan*/  RGN_DIFF ; 
 int TRUE ; 
 int calc_y_offset (TYPE_5__*,TYPE_13__*) ; 
 int /*<<< orphan*/  draw_text (TYPE_5__*,TYPE_4__*,int,int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  get_selection_rect (TYPE_5__*,TYPE_4__*,int,int,int,TYPE_3__*) ; 

__attribute__((used)) static void ME_DrawTextWithStyle(ME_Context *c, ME_Run *run, int x, int y,
                                 int nSelFrom, int nSelTo, int ymin, int cy)
{
  HDC hDC = c->hDC;
  HGDIOBJ hOldFont;
  int yOffset = 0;
  BOOL selected = (nSelFrom < run->len && nSelTo >= 0
                   && nSelFrom < nSelTo && !c->editor->bHideSelection &&
                   (c->editor->bHaveFocus || (c->editor->styleFlags & ES_NOHIDESEL)));
  BOOL old_style_selected = FALSE;
  RECT sel_rect;
  HRGN clip = NULL, sel_rgn = NULL;

  yOffset = calc_y_offset( c, run->style );

  if (selected)
  {
    get_selection_rect( c, run, nSelFrom, nSelTo, cy, &sel_rect );
    OffsetRect( &sel_rect, x, ymin );

    if (c->editor->bEmulateVersion10)
    {
      old_style_selected = TRUE;
      selected = FALSE;
    }
    else
    {
      sel_rgn = CreateRectRgnIndirect( &sel_rect );
      clip = CreateRectRgn( 0, 0, 0, 0 );
      if (GetClipRgn( hDC, clip ) != 1)
      {
        DeleteObject( clip );
        clip = NULL;
      }
    }
  }

  hOldFont = ME_SelectStyleFont( c, run->style );

  if (sel_rgn) ExtSelectClipRgn( hDC, sel_rgn, RGN_DIFF );

  if (!(run->style->fmt.dwEffects & CFE_AUTOBACKCOLOR)
      && (run->style->fmt.dwMask & CFM_BACKCOLOR) )
  {
    RECT tmp_rect;
    get_selection_rect( c, run, 0, run->len, cy, &tmp_rect );
    OffsetRect( &tmp_rect, x, ymin );
    draw_text( c, run, x, y - yOffset, FALSE, &tmp_rect );
  }
  else
    draw_text( c, run, x, y - yOffset, FALSE, NULL );

  if (sel_rgn)
  {
    ExtSelectClipRgn( hDC, clip, RGN_COPY );
    ExtSelectClipRgn( hDC, sel_rgn, RGN_AND );
    draw_text( c, run, x, y - yOffset, TRUE, &sel_rect );
    ExtSelectClipRgn( hDC, clip, RGN_COPY );
    if (clip) DeleteObject( clip );
    DeleteObject( sel_rgn );
  }

  if (old_style_selected)
    PatBlt( hDC, sel_rect.left, ymin, sel_rect.right - sel_rect.left, cy, DSTINVERT );

  ME_UnselectStyleFont(c, run->style, hOldFont);
}