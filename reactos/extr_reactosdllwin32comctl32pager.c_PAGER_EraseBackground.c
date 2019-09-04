#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_7__ {int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_6__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__ PAGER_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  OffsetWindowOrgEx (scalar_t__,scalar_t__,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowOrgEx (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_ERASEBKGND ; 

__attribute__((used)) static LRESULT
PAGER_EraseBackground (const PAGER_INFO* infoPtr, HDC hdc)
{
    POINT pt, ptorig;
    HWND parent;
    LRESULT ret;

    pt.x = 0;
    pt.y = 0;
    parent = GetParent(infoPtr->hwndSelf);
    MapWindowPoints(infoPtr->hwndSelf, parent, &pt, 1);
    OffsetWindowOrgEx (hdc, pt.x, pt.y, &ptorig);
    ret = SendMessageW (parent, WM_ERASEBKGND, (WPARAM)hdc, 0);
    SetWindowOrgEx (hdc, ptorig.x, ptorig.y, 0);

    return ret;
}