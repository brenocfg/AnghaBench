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
typedef  int UINT ;
struct TYPE_6__ {int tmHeight; int tmExternalLeading; } ;
struct TYPE_5__ {int normalImageHeight; int dwStyle; int /*<<< orphan*/  hFont; } ;
typedef  TYPE_1__ TREEVIEW_INFO ;
typedef  TYPE_2__ TEXTMETRICW ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextMetricsW (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TVHEIGHT_FONT_ADJUST ; 
 int TVHEIGHT_MIN ; 
 int TVS_NONEVENHEIGHT ; 

__attribute__((used)) static UINT
TREEVIEW_NaturalHeight(const TREEVIEW_INFO *infoPtr)
{
    TEXTMETRICW tm;
    HDC hdc = GetDC(0);
    HFONT hOldFont = SelectObject(hdc, infoPtr->hFont);
    UINT height;

    /* Height is the maximum of:
     * 16 (a hack because our fonts are tiny), and
     * The text height + border & margin, and
     * The size of the normal image list
     */
    GetTextMetricsW(hdc, &tm);
    SelectObject(hdc, hOldFont);
    ReleaseDC(0, hdc);

    height = TVHEIGHT_MIN;
    if (height < tm.tmHeight + tm.tmExternalLeading + TVHEIGHT_FONT_ADJUST)
        height = tm.tmHeight + tm.tmExternalLeading + TVHEIGHT_FONT_ADJUST;
    if (height < infoPtr->normalImageHeight)
        height = infoPtr->normalImageHeight;

    /* Round down, unless we support odd ("non even") heights. */
    if (!(infoPtr->dwStyle & TVS_NONEVENHEIGHT))
        height &= ~1;

    return height;
}