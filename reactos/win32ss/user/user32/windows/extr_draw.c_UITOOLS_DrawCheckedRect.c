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
struct TYPE_6__ {scalar_t__ hbrGray; } ;
struct TYPE_5__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__* LPRECT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBRUSH ;
typedef  scalar_t__ COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BTNFACE ; 
 int /*<<< orphan*/  COLOR_BTNHIGHLIGHT ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PatBlt (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ RGB (int,int,int) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SetBkColor (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* gpsi ; 

__attribute__((used)) static void UITOOLS_DrawCheckedRect( HDC dc, LPRECT rect )
{
    if(GetSysColor(COLOR_BTNHIGHLIGHT) == RGB(255, 255, 255))
    {
        HBRUSH hbsave;
        COLORREF bg;

        FillRect(dc, rect, GetSysColorBrush(COLOR_BTNFACE));
        bg = SetBkColor(dc, RGB(255, 255, 255));
        hbsave = (HBRUSH)SelectObject(dc, gpsi->hbrGray);
        PatBlt(dc, rect->left, rect->top, rect->right-rect->left, rect->bottom-rect->top, 0x00FA0089);
        SelectObject(dc, hbsave);
        SetBkColor(dc, bg);
    }
    else
    {
        FillRect(dc, rect, GetSysColorBrush(COLOR_BTNHIGHLIGHT));
    }
}