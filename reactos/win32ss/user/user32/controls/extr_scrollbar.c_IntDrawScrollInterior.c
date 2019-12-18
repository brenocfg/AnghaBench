#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_8__ {scalar_t__ xyThumbBottom; scalar_t__ xyThumbTop; int* rgstate; scalar_t__ dxyLineButton; TYPE_1__ rcScrollBar; } ;
struct TYPE_7__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PSCROLLBARINFO ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBRUSH ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BF_MIDDLE ; 
 int BF_RECT ; 
 int /*<<< orphan*/  BLACKNESS ; 
 int /*<<< orphan*/  COLOR_SCROLLBAR ; 
 int /*<<< orphan*/  CTLCOLOR_SCROLLBAR ; 
 scalar_t__ DefWndControlColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDGE_RAISED ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetControlBrush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATCOPY ; 
 int /*<<< orphan*/  PatBlt (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SB_CTL ; 
 size_t SCROLL_BOTTOM_RECT ; 
 size_t SCROLL_TOP_RECT ; 
 int STATE_SYSTEM_PRESSED ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_CTLCOLORSCROLLBAR ; 

__attribute__((used)) static void
IntDrawScrollInterior(HWND hWnd, HDC hDC, INT nBar, BOOL Vertical,
   PSCROLLBARINFO ScrollBarInfo)
{
   INT ThumbSize = ScrollBarInfo->xyThumbBottom - ScrollBarInfo->xyThumbTop;
   INT ThumbTop = ScrollBarInfo->xyThumbTop;
   RECT Rect;
   HBRUSH hSaveBrush, hBrush;
   BOOL TopSelected = FALSE, BottomSelected = FALSE;

   if (ScrollBarInfo->rgstate[SCROLL_TOP_RECT] & STATE_SYSTEM_PRESSED)
      TopSelected = TRUE;
   if (ScrollBarInfo->rgstate[SCROLL_BOTTOM_RECT] & STATE_SYSTEM_PRESSED)
      BottomSelected = TRUE;

   /*
    * Only scrollbar controls send WM_CTLCOLORSCROLLBAR.
    * The window-owned scrollbars need to call DefWndControlColor
    * to correctly setup default scrollbar colors
    */
   if (nBar == SB_CTL)
   {
      hBrush = GetControlBrush( hWnd, hDC, WM_CTLCOLORSCROLLBAR);
      if (!hBrush)
         hBrush = GetSysColorBrush(COLOR_SCROLLBAR);
   }
   else
   {
      hBrush = DefWndControlColor(hDC, CTLCOLOR_SCROLLBAR);
   }

   hSaveBrush = SelectObject(hDC, hBrush);

   /* Calculate the scroll rectangle */
   if (Vertical)
   {
      Rect.top = ScrollBarInfo->rcScrollBar.top + ScrollBarInfo->dxyLineButton;
      Rect.bottom = ScrollBarInfo->rcScrollBar.bottom - ScrollBarInfo->dxyLineButton;
      Rect.left = ScrollBarInfo->rcScrollBar.left;
      Rect.right = ScrollBarInfo->rcScrollBar.right;
   }
   else
   {
      Rect.top = ScrollBarInfo->rcScrollBar.top;
      Rect.bottom = ScrollBarInfo->rcScrollBar.bottom;
      Rect.left = ScrollBarInfo->rcScrollBar.left + ScrollBarInfo->dxyLineButton;
      Rect.right = ScrollBarInfo->rcScrollBar.right - ScrollBarInfo->dxyLineButton;
   }

   /* Draw the scroll rectangles and thumb */
   if (!ScrollBarInfo->xyThumbBottom)
   {
      PatBlt(hDC, Rect.left, Rect.top, Rect.right - Rect.left,
         Rect.bottom - Rect.top, PATCOPY);

      /* Cleanup and return */
      SelectObject(hDC, hSaveBrush);
      return;
   }

   ThumbTop -= ScrollBarInfo->dxyLineButton;

   if (ScrollBarInfo->dxyLineButton)
   {
      if (Vertical)
      {
         if (ThumbSize)
         {
            PatBlt(hDC, Rect.left, Rect.top, Rect.right - Rect.left,
                   ThumbTop, TopSelected ? BLACKNESS : PATCOPY);
            Rect.top += ThumbTop;
            PatBlt(hDC, Rect.left, Rect.top + ThumbSize, Rect.right - Rect.left,
               Rect.bottom - Rect.top - ThumbSize, BottomSelected ? BLACKNESS : PATCOPY);
            Rect.bottom = Rect.top + ThumbSize;
         }
         else
         {
            if (ThumbTop)
            {
               PatBlt(hDC, Rect.left, ScrollBarInfo->dxyLineButton,
                  Rect.right - Rect.left, Rect.bottom - Rect.top, PATCOPY);
            }
         }
      }
      else
      {
         if (ThumbSize)
         {
            PatBlt(hDC, Rect.left, Rect.top, ThumbTop,
               Rect.bottom - Rect.top, TopSelected ? BLACKNESS : PATCOPY);
            Rect.left += ThumbTop;
            PatBlt(hDC, Rect.left + ThumbSize, Rect.top,
               Rect.right - Rect.left - ThumbSize, Rect.bottom - Rect.top,
               BottomSelected ? BLACKNESS : PATCOPY);
            Rect.right = Rect.left + ThumbSize;
         }
         else
         {
            if (ThumbTop)
            {
               PatBlt(hDC, ScrollBarInfo->dxyLineButton, Rect.top,
                  Rect.right - Rect.left, Rect.bottom - Rect.top, PATCOPY);
            }
         }
      }
   }

   /* Draw the thumb */
   if (ThumbSize)
      DrawEdge(hDC, &Rect, EDGE_RAISED, BF_RECT | BF_MIDDLE);

   /* Cleanup */
   SelectObject(hDC, hSaveBrush);
}