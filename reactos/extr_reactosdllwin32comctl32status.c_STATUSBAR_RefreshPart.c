#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ right; scalar_t__ left; } ;
struct TYPE_11__ {TYPE_7__ bound; } ;
struct TYPE_10__ {scalar_t__ clrBk; int /*<<< orphan*/  Self; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  TYPE_2__ STATUSWINDOWPART ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;

/* Variables and functions */
 scalar_t__ CLR_DEFAULT ; 
 int /*<<< orphan*/  COLOR_3DFACE ; 
 int /*<<< orphan*/  CreateSolidBrush (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RectVisible (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  STATUSBAR_DrawPart (TYPE_1__ const*,int /*<<< orphan*/ ,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 

__attribute__((used)) static void
STATUSBAR_RefreshPart (const STATUS_INFO *infoPtr, HDC hdc, const STATUSWINDOWPART *part, int itemID)
{
    HBRUSH hbrBk;
    HTHEME theme;

    TRACE("item %d\n", itemID);

    if (part->bound.right < part->bound.left) return;

    if (!RectVisible(hdc, &part->bound))
        return;

    if ((theme = GetWindowTheme (infoPtr->Self)))
    {
        RECT cr;
        GetClientRect (infoPtr->Self, &cr);
        DrawThemeBackground(theme, hdc, 0, 0, &cr, &part->bound);
    }
    else
    {
        if (infoPtr->clrBk != CLR_DEFAULT)
                hbrBk = CreateSolidBrush (infoPtr->clrBk);
        else
                hbrBk = GetSysColorBrush (COLOR_3DFACE);
        FillRect(hdc, &part->bound, hbrBk);
        if (infoPtr->clrBk != CLR_DEFAULT)
                DeleteObject (hbrBk);
    }

    STATUSBAR_DrawPart (infoPtr, hdc, part, itemID);
}