#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ clr3dHilight; scalar_t__ clrWindow; int /*<<< orphan*/  clr3dFace; } ;
struct TYPE_9__ {int bottom; int top; scalar_t__ right; scalar_t__ left; } ;
struct TYPE_8__ {int dwStyle; int flags; TYPE_2__ rcThumb; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  TYPE_2__ RECT ;
typedef  scalar_t__ HTHEME ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;

/* Variables and functions */
 int BF_BOTTOM ; 
 int BF_DIAGONAL_ENDBOTTOMLEFT ; 
 int BF_DIAGONAL_ENDBOTTOMRIGHT ; 
 int BF_DIAGONAL_ENDTOPLEFT ; 
 int BF_DIAGONAL_ENDTOPRIGHT ; 
 int BF_LEFT ; 
 int BF_RECT ; 
 int BF_RIGHT ; 
 int BF_SOFT ; 
 int BF_TOP ; 
 int /*<<< orphan*/  COLOR_BTNFACE ; 
 int /*<<< orphan*/  COLOR_SCROLLBAR ; 
 int /*<<< orphan*/  COMCTL32_hPattern55AABrush ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DrawThemeBackground (scalar_t__,int /*<<< orphan*/ ,int,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDGE_RAISED ; 
 int /*<<< orphan*/  EDGE_SUNKEN ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TBS_BOTH ; 
 int TBS_LEFT ; 
 int TBS_TOP ; 
 int TBS_VERT ; 
 int TB_DRAG_MODE ; 
 int TB_THUMB_HOT ; 
 int TKP_THUMB ; 
 int TKP_THUMBBOTTOM ; 
 int TKP_THUMBLEFT ; 
 int TKP_THUMBRIGHT ; 
 int TKP_THUMBTOP ; 
 int TKP_THUMBVERT ; 
 int TRACKBAR_FillThumb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TUS_DISABLED ; 
 int TUS_HOT ; 
 int TUS_NORMAL ; 
 int TUS_PRESSED ; 
 int WS_DISABLED ; 
 TYPE_3__ comctl32_color ; 

__attribute__((used)) static void
TRACKBAR_DrawThumb (TRACKBAR_INFO *infoPtr, HDC hdc)
{
    HTHEME theme = GetWindowTheme (infoPtr->hwndSelf);
    int PointDepth;
    HBRUSH brush;

    if (theme)
    {
        int partId;
        int stateId;
        if (infoPtr->dwStyle & TBS_BOTH)
            partId = (infoPtr->dwStyle & TBS_VERT) ? TKP_THUMBVERT : TKP_THUMB;
        else if (infoPtr->dwStyle & TBS_LEFT)
            partId = (infoPtr->dwStyle & TBS_VERT) ? TKP_THUMBLEFT : TKP_THUMBTOP;
        else
            partId = (infoPtr->dwStyle & TBS_VERT) ? TKP_THUMBRIGHT : TKP_THUMBBOTTOM;
            
        if (infoPtr->dwStyle & WS_DISABLED)
            stateId = TUS_DISABLED;
        else if (infoPtr->flags & TB_DRAG_MODE)
            stateId = TUS_PRESSED;
        else if (infoPtr->flags & TB_THUMB_HOT)
            stateId = TUS_HOT;
        else
            stateId = TUS_NORMAL;
        
        DrawThemeBackground (theme, hdc, partId, stateId, &infoPtr->rcThumb, NULL);
        
        return;
    }

    if (infoPtr->dwStyle & WS_DISABLED || infoPtr->flags & TB_DRAG_MODE)
    {
        if (comctl32_color.clr3dHilight == comctl32_color.clrWindow)
            brush = COMCTL32_hPattern55AABrush;
        else
            brush = GetSysColorBrush(COLOR_SCROLLBAR);

        SetTextColor(hdc, comctl32_color.clr3dFace);
        SetBkColor(hdc, comctl32_color.clr3dHilight);
    }
    else
        brush = GetSysColorBrush(COLOR_BTNFACE);

    PointDepth = TRACKBAR_FillThumb(infoPtr, hdc, brush);

    if (infoPtr->dwStyle & TBS_BOTH)
    {
       DrawEdge(hdc, &infoPtr->rcThumb, EDGE_RAISED, BF_RECT | BF_SOFT);
       return;
    }
    else
    {
        RECT thumb = infoPtr->rcThumb;

        if (infoPtr->dwStyle & TBS_VERT)
        {
          if (infoPtr->dwStyle & TBS_LEFT)
          {
            /* rectangular part */
            thumb.left += PointDepth;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_TOP | BF_RIGHT | BF_BOTTOM | BF_SOFT);

            /* light edge */
            thumb.left -= PointDepth;
            thumb.right = thumb.left + PointDepth;
            thumb.bottom = infoPtr->rcThumb.top + PointDepth + 1;
            thumb.top = infoPtr->rcThumb.top;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_DIAGONAL_ENDTOPRIGHT | BF_SOFT);

            /* shadowed edge */
            thumb.top += PointDepth;
            thumb.bottom += PointDepth;
            DrawEdge(hdc, &thumb, EDGE_SUNKEN, BF_DIAGONAL_ENDTOPLEFT | BF_SOFT);
            return;
          }
          else
          {
            /* rectangular part */
            thumb.right -= PointDepth;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_TOP | BF_LEFT | BF_BOTTOM | BF_SOFT);

            /* light edge */
            thumb.left = thumb.right;
            thumb.right += PointDepth + 1;
            thumb.bottom = infoPtr->rcThumb.top + PointDepth + 1;
            thumb.top = infoPtr->rcThumb.top;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_DIAGONAL_ENDTOPLEFT | BF_SOFT);

            /* shadowed edge */
            thumb.top += PointDepth;
            thumb.bottom += PointDepth;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_DIAGONAL_ENDBOTTOMLEFT | BF_SOFT);
          }
        }
        else
        {
          if (infoPtr->dwStyle & TBS_TOP)
          {
            /* rectangular part */
            thumb.top += PointDepth;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_LEFT | BF_BOTTOM | BF_RIGHT | BF_SOFT);

            /* light edge */
            thumb.left = infoPtr->rcThumb.left;
            thumb.right = thumb.left + PointDepth;
            thumb.bottom = infoPtr->rcThumb.top + PointDepth + 1;
            thumb.top -= PointDepth;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_DIAGONAL_ENDTOPRIGHT | BF_SOFT);

            /* shadowed edge */
            thumb.left += PointDepth;
            thumb.right += PointDepth;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_DIAGONAL_ENDBOTTOMRIGHT | BF_SOFT);
          }
          else
          {
            /* rectangular part */
            thumb.bottom -= PointDepth;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_LEFT | BF_TOP | BF_RIGHT | BF_SOFT);

            /* light edge */
            thumb.left = infoPtr->rcThumb.left;
            thumb.right = thumb.left + PointDepth;
            thumb.top = infoPtr->rcThumb.bottom - PointDepth - 1;
            thumb.bottom += PointDepth;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_DIAGONAL_ENDTOPLEFT | BF_SOFT);

            /* shadowed edge */
            thumb.left += PointDepth;
            thumb.right += PointDepth;
            DrawEdge(hdc, &thumb, EDGE_RAISED, BF_DIAGONAL_ENDBOTTOMLEFT | BF_SOFT);
          }
        }
    }
}