#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bottom; scalar_t__ left; scalar_t__ top; scalar_t__ right; } ;
struct TYPE_7__ {TYPE_2__* rcRebar; TYPE_1__ rcClient; int /*<<< orphan*/ ** hRebar; } ;
struct TYPE_6__ {scalar_t__ bottom; scalar_t__ right; } ;
typedef  TYPE_3__* PTOOLBAR_DOCKS ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/ * HDWP ;

/* Variables and functions */
 size_t BOTTOM_DOCK ; 
 int /*<<< orphan*/ * DeferWindowPos (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t LEFT_DOCK ; 
 size_t RIGHT_DOCK ; 
 int /*<<< orphan*/  SWP_NOZORDER ; 
 size_t TOP_DOCK ; 

HDWP
TbdDeferDocks(HDWP hWinPosInfo,
              PTOOLBAR_DOCKS TbDocks)
{
    LONG cx, cy;
    HDWP hRet = hWinPosInfo;

    cx = TbDocks->rcClient.right - TbDocks->rcClient.left;
    cy = TbDocks->rcClient.bottom - TbDocks->rcClient.top;

    /* Top dock */
    if (TbDocks->hRebar[TOP_DOCK] != NULL)
    {
        hRet = DeferWindowPos(hRet,
                              TbDocks->hRebar[TOP_DOCK],
                              NULL,
                              TbDocks->rcClient.left - TbDocks->rcRebar[LEFT_DOCK].right,
                              TbDocks->rcClient.top - TbDocks->rcRebar[TOP_DOCK].bottom,
                              cx + TbDocks->rcRebar[LEFT_DOCK].right + TbDocks->rcRebar[RIGHT_DOCK].right,
                              TbDocks->rcRebar[TOP_DOCK].bottom,
                              SWP_NOZORDER);
        if (hRet == NULL)
            return NULL;
    }

    /* Left dock */
    if (TbDocks->hRebar[LEFT_DOCK] != NULL)
    {
        hRet = DeferWindowPos(hRet,
                              TbDocks->hRebar[LEFT_DOCK],
                              NULL,
                              TbDocks->rcClient.left - TbDocks->rcRebar[LEFT_DOCK].right,
                              TbDocks->rcClient.top,
                              TbDocks->rcRebar[LEFT_DOCK].right,
                              cy,
                              SWP_NOZORDER);
        if (hRet == NULL)
            return NULL;
    }

    /* Right dock */
    if (TbDocks->hRebar[RIGHT_DOCK] != NULL)
    {
        hRet = DeferWindowPos(hRet,
                              TbDocks->hRebar[RIGHT_DOCK],
                              NULL,
                              TbDocks->rcClient.right,
                              TbDocks->rcClient.top,
                              TbDocks->rcRebar[RIGHT_DOCK].right,
                              cy,
                              SWP_NOZORDER);
        if (hRet == NULL)
            return NULL;
    }

    /* Bottom dock */
    if (TbDocks->hRebar[BOTTOM_DOCK] != NULL)
    {
        hRet = DeferWindowPos(hRet,
                              TbDocks->hRebar[BOTTOM_DOCK],
                              NULL,
                              TbDocks->rcClient.left - TbDocks->rcRebar[LEFT_DOCK].right,
                              TbDocks->rcClient.bottom,
                              cx + TbDocks->rcRebar[LEFT_DOCK].right + TbDocks->rcRebar[RIGHT_DOCK].right,
                              TbDocks->rcRebar[BOTTOM_DOCK].bottom,
                              SWP_NOZORDER);
        if (hRet == NULL)
            return NULL;
    }

    return hRet;
}