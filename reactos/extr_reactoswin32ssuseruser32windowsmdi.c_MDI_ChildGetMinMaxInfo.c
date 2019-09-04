#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_9__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_12__ {TYPE_2__ ptMaxPosition; TYPE_1__ ptMaxSize; } ;
struct TYPE_11__ {scalar_t__ top; scalar_t__ left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__ MINMAXINFO ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustWindowRectEx (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_3__*) ; 

__attribute__((used)) static void MDI_ChildGetMinMaxInfo( HWND client, HWND hwnd, MINMAXINFO* lpMinMax )
{
    RECT rect;

    GetClientRect( client, &rect );
    AdjustWindowRectEx( &rect, GetWindowLongPtrW( hwnd, GWL_STYLE ),
                        0, GetWindowLongPtrW( hwnd, GWL_EXSTYLE ));

    lpMinMax->ptMaxSize.x = rect.right -= rect.left;
    lpMinMax->ptMaxSize.y = rect.bottom -= rect.top;

    lpMinMax->ptMaxPosition.x = rect.left;
    lpMinMax->ptMaxPosition.y = rect.top;

    TRACE("max rect %s\n", wine_dbgstr_rect(&rect));
}