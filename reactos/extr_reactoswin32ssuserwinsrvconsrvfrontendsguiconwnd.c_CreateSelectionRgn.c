#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ Y; scalar_t__ X; } ;
struct TYPE_14__ {scalar_t__ X; } ;
struct TYPE_17__ {TYPE_1__ ScreenBufferSize; } ;
struct TYPE_16__ {TYPE_5__* ActiveBuffer; } ;
struct TYPE_15__ {scalar_t__ Left; scalar_t__ Top; scalar_t__ Right; scalar_t__ Bottom; } ;
typedef  TYPE_2__ SMALL_RECT ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_2__* PSMALL_RECT ;
typedef  TYPE_4__* PGUI_CONSOLE_DATA ;
typedef  int /*<<< orphan*/  PCOORD ;
typedef  TYPE_5__* PCONSOLE_SCREEN_BUFFER ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  TYPE_6__ COORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgnIndirect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSelectionBeginEnd (TYPE_6__*,TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  RGN_XOR ; 
 int /*<<< orphan*/  SmallRectToRect (TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static HRGN
CreateSelectionRgn(PGUI_CONSOLE_DATA GuiData,
                   BOOL LineSelection,
                   PCOORD SelectionAnchor,
                   PSMALL_RECT SmallRect)
{
    if (!LineSelection)
    {
        RECT rect;
        SmallRectToRect(GuiData, &rect, SmallRect);
        return CreateRectRgnIndirect(&rect);
    }
    else
    {
        HRGN SelRgn;
        COORD Begin, End;

        GetSelectionBeginEnd(&Begin, &End, SelectionAnchor, SmallRect);

        if (Begin.Y == End.Y)
        {
            SMALL_RECT sr;
            RECT       r ;

            sr.Left   = Begin.X;
            sr.Top    = Begin.Y;
            sr.Right  = End.X;
            sr.Bottom = End.Y;

            // Debug thingie to see whether I can put this corner case
            // together with the previous one.
            if (SmallRect->Left   != sr.Left  ||
                SmallRect->Top    != sr.Top   ||
                SmallRect->Right  != sr.Right ||
                SmallRect->Bottom != sr.Bottom)
            {
                DPRINT1("\n"
                        "SmallRect = (%d, %d, %d, %d)\n"
                        "sr = (%d, %d, %d, %d)\n"
                        "\n",
                        SmallRect->Left, SmallRect->Top, SmallRect->Right, SmallRect->Bottom,
                        sr.Left, sr.Top, sr.Right, sr.Bottom);
            }

            SmallRectToRect(GuiData, &r, &sr);
            SelRgn = CreateRectRgnIndirect(&r);
        }
        else
        {
            PCONSOLE_SCREEN_BUFFER ActiveBuffer = GuiData->ActiveBuffer;

            HRGN       rg1, rg2, rg3;
            SMALL_RECT sr1, sr2, sr3;
            RECT       r1 , r2 , r3 ;

            sr1.Left   = Begin.X;
            sr1.Top    = Begin.Y;
            sr1.Right  = ActiveBuffer->ScreenBufferSize.X - 1;
            sr1.Bottom = Begin.Y;

            sr2.Left   = 0;
            sr2.Top    = Begin.Y + 1;
            sr2.Right  = ActiveBuffer->ScreenBufferSize.X - 1;
            sr2.Bottom = End.Y - 1;

            sr3.Left   = 0;
            sr3.Top    = End.Y;
            sr3.Right  = End.X;
            sr3.Bottom = End.Y;

            SmallRectToRect(GuiData, &r1, &sr1);
            SmallRectToRect(GuiData, &r2, &sr2);
            SmallRectToRect(GuiData, &r3, &sr3);

            rg1 = CreateRectRgnIndirect(&r1);
            rg2 = CreateRectRgnIndirect(&r2);
            rg3 = CreateRectRgnIndirect(&r3);

            CombineRgn(rg1, rg1, rg2, RGN_XOR);
            CombineRgn(rg1, rg1, rg3, RGN_XOR);
            DeleteObject(rg3);
            DeleteObject(rg2);

            SelRgn = rg1;
        }

        return SelRgn;
    }
}