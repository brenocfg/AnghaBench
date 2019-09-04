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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  (* ParentResize ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;int /*<<< orphan*/  hParent; TYPE_1__* rcRebar; int /*<<< orphan*/ * hRebar; } ;
struct TYPE_7__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {void* right; void* bottom; scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PTOOLBAR_DOCKS ;
typedef  void* LONG ;
typedef  size_t DOCK_POSITION ;

/* Variables and functions */
#define  BOTTOM_DOCK 131 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
#define  LEFT_DOCK 130 
 int /*<<< orphan*/  RB_GETBARHEIGHT ; 
#define  RIGHT_DOCK 129 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TOP_DOCK 128 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static VOID
TbnRebarChangeSize(PTOOLBAR_DOCKS TbDocks,
                   DOCK_POSITION Position)
{
    LONG cRebar;

    TbDocks->rcRebar[Position].left = 0;
    TbDocks->rcRebar[Position].top = 0;

    cRebar = (LONG)SendMessage(TbDocks->hRebar[Position],
                               RB_GETBARHEIGHT,
                               0,
                               0);

    switch (Position)
    {
        case TOP_DOCK:
        case BOTTOM_DOCK:
            TbDocks->rcRebar[Position].bottom = cRebar;
            break;

        case LEFT_DOCK:
        case RIGHT_DOCK:
            TbDocks->rcRebar[Position].right = cRebar;
            break;

        default:
            break;
    }

    if (TbDocks->ParentResize != NULL)
    {
        RECT rcClient = {0};

        GetClientRect(TbDocks->hParent,
                      &rcClient);

        TbDocks->ParentResize(TbDocks->Context,
                              rcClient.right - rcClient.left,
                              rcClient.bottom - rcClient.top);
    }
}