#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  hFont; int /*<<< orphan*/  nHeight; } ;
struct TYPE_5__ {int /*<<< orphan*/  tmHeight; } ;
typedef  TYPE_1__ TEXTMETRICW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ HOTKEY_INFO ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextMetricsW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
HOTKEY_SetFont (HOTKEY_INFO *infoPtr, HFONT hFont, BOOL redraw)
{
    TEXTMETRICW tm;
    HDC hdc;
    HFONT hOldFont = 0;

    infoPtr->hFont = hFont;

    hdc = GetDC (infoPtr->hwndSelf);
    if (infoPtr->hFont)
	hOldFont = SelectObject (hdc, infoPtr->hFont);

    GetTextMetricsW (hdc, &tm);
    infoPtr->nHeight = tm.tmHeight;

    if (infoPtr->hFont)
	SelectObject (hdc, hOldFont);
    ReleaseDC (infoPtr->hwndSelf, hdc);

    if (redraw)
	InvalidateRect (infoPtr->hwndSelf, NULL, TRUE);

    return 0;
}