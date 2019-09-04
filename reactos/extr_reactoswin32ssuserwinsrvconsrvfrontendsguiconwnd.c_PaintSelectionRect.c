#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int /*<<< orphan*/  srSelection; int /*<<< orphan*/  dwSelectionAnchor; } ;
struct TYPE_9__ {TYPE_1__ Selection; int /*<<< orphan*/  LineSelection; } ;
struct TYPE_8__ {int /*<<< orphan*/  hdc; int /*<<< orphan*/  rcPaint; } ;
typedef  TYPE_2__* PPAINTSTRUCT ;
typedef  TYPE_3__* PGUI_CONSOLE_DATA ;
typedef  int /*<<< orphan*/  HRGN ;

/* Variables and functions */
 int CombineRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgnIndirect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateSelectionRgn (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int ERROR ; 
 int /*<<< orphan*/  InvertRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NULLREGION ; 
 int /*<<< orphan*/  RGN_AND ; 

__attribute__((used)) static VOID
PaintSelectionRect(PGUI_CONSOLE_DATA GuiData, PPAINTSTRUCT pps)
{
    HRGN rgnPaint = CreateRectRgnIndirect(&pps->rcPaint);
    HRGN rgnSel   = CreateSelectionRgn(GuiData, GuiData->LineSelection,
                                       &GuiData->Selection.dwSelectionAnchor,
                                       &GuiData->Selection.srSelection);

    /* Invert the selection */

    int ErrorCode = CombineRgn(rgnPaint, rgnPaint, rgnSel, RGN_AND);
    if (ErrorCode != ERROR && ErrorCode != NULLREGION)
    {
        InvertRgn(pps->hdc, rgnPaint);
    }

    DeleteObject(rgnSel);
    DeleteObject(rgnPaint);
}