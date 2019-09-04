#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
struct TYPE_18__ {int /*<<< orphan*/  clrWindowText; int /*<<< orphan*/  clrWindow; int /*<<< orphan*/  clrActiveCaption; int /*<<< orphan*/  clrGrayText; } ;
struct TYPE_14__ {int right; } ;
struct TYPE_16__ {int bottom; int left; int right; int /*<<< orphan*/  top; } ;
struct TYPE_17__ {int dwStyle; int nrFields; int select; int nCharsEntered; scalar_t__ bCalDepressed; int /*<<< orphan*/  calbutton; int /*<<< orphan*/  charsEntered; scalar_t__ haveFocus; TYPE_3__* fieldRect; TYPE_1__ checkbox; int /*<<< orphan*/  hFont; TYPE_3__ rcDraw; scalar_t__ dateValid; } ;
struct TYPE_15__ {int cy; int cx; } ;
typedef  TYPE_2__ SIZE ;
typedef  int SHORT ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  TYPE_4__ DATETIME_INFO ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATETIME_ReturnFieldWidth (TYPE_4__*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  DATETIME_ReturnTxt (TYPE_4__*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int DFCS_INACTIVE ; 
 int DFCS_PUSHED ; 
 int DFCS_SCROLLDOWN ; 
 int /*<<< orphan*/  DFC_SCROLL ; 
 int DTS_SHOWNONE ; 
 int DTS_UPDOWN ; 
 int DT_CENTER ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawFrameControl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRANSPARENT ; 
 int WS_DISABLED ; 
 TYPE_5__ comctl32_color ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlenW (scalar_t__*) ; 

__attribute__((used)) static void 
DATETIME_Refresh (DATETIME_INFO *infoPtr, HDC hdc)
{
    TRACE("\n");

    if (infoPtr->dateValid) {
        int i, prevright;
        RECT *field;
        RECT *rcDraw = &infoPtr->rcDraw;
        SIZE size;
        COLORREF oldTextColor;
        SHORT fieldWidth = 0;
        HFONT oldFont = SelectObject (hdc, infoPtr->hFont);
        INT oldBkMode = SetBkMode (hdc, TRANSPARENT);
        WCHAR txt[80];

        DATETIME_ReturnTxt (infoPtr, 0, txt, ARRAY_SIZE(txt));
        GetTextExtentPoint32W (hdc, txt, strlenW(txt), &size);
        rcDraw->bottom = size.cy + 2;

        prevright = infoPtr->checkbox.right = ((infoPtr->dwStyle & DTS_SHOWNONE) ? 18 : 2);

        for (i = 0; i < infoPtr->nrFields; i++) {
            DATETIME_ReturnTxt (infoPtr, i, txt, ARRAY_SIZE(txt));
            GetTextExtentPoint32W (hdc, txt, strlenW(txt), &size);
            DATETIME_ReturnFieldWidth (infoPtr, hdc, i, &fieldWidth);
            field = &infoPtr->fieldRect[i];
            field->left   = prevright;
            field->right  = prevright + fieldWidth;
            field->top    = rcDraw->top;
            field->bottom = rcDraw->bottom;
            prevright = field->right;

            if (infoPtr->dwStyle & WS_DISABLED)
                oldTextColor = SetTextColor (hdc, comctl32_color.clrGrayText);
            else if ((infoPtr->haveFocus) && (i == infoPtr->select)) {
                RECT selection;

                /* fill if focused */
                HBRUSH hbr = CreateSolidBrush (comctl32_color.clrActiveCaption);

                if (infoPtr->nCharsEntered)
                {
                    memcpy(txt, infoPtr->charsEntered, infoPtr->nCharsEntered * sizeof(WCHAR));
                    txt[infoPtr->nCharsEntered] = 0;
                    GetTextExtentPoint32W (hdc, txt, strlenW(txt), &size);
                }

                SetRect(&selection, 0, 0, size.cx, size.cy);
                /* center rectangle */
                OffsetRect(&selection, (field->right  + field->left - size.cx)/2,
                                       (field->bottom - size.cy)/2);

                FillRect(hdc, &selection, hbr);
                DeleteObject (hbr);
                oldTextColor = SetTextColor (hdc, comctl32_color.clrWindow);
            }
            else
                oldTextColor = SetTextColor (hdc, comctl32_color.clrWindowText);

            /* draw the date text using the colour set above */
            DrawTextW (hdc, txt, strlenW(txt), field, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            SetTextColor (hdc, oldTextColor);
        }
        SetBkMode (hdc, oldBkMode);
        SelectObject (hdc, oldFont);
    }

    if (!(infoPtr->dwStyle & DTS_UPDOWN)) {
        DrawFrameControl(hdc, &infoPtr->calbutton, DFC_SCROLL,
                         DFCS_SCROLLDOWN | (infoPtr->bCalDepressed ? DFCS_PUSHED : 0) |
                         (infoPtr->dwStyle & WS_DISABLED ? DFCS_INACTIVE : 0) );
    }
}