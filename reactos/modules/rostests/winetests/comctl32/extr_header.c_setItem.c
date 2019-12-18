#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cchTextMax; int /*<<< orphan*/  pszText; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ HDITEMA ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HDI_TEXT ; 
 int /*<<< orphan*/  HDM_SETITEMA ; 
 int /*<<< orphan*/  HDN_ITEMCHANGEDA ; 
 int /*<<< orphan*/  HDN_ITEMCHANGINGA ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  notifies_received () ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static LONG setItem(HWND hdex, int idx, LPSTR text, BOOL fCheckNotifies)
{
    LONG ret;
    HDITEMA hdexItem;
    hdexItem.mask       = HDI_TEXT;
    hdexItem.pszText    = text;
    hdexItem.cchTextMax = 0;
    if (fCheckNotifies)
    {
        expect_notify(HDN_ITEMCHANGINGA, FALSE, &hdexItem);
        expect_notify(HDN_ITEMCHANGEDA, FALSE, &hdexItem);
    }
    ret = SendMessageA(hdex, HDM_SETITEMA, idx, (LPARAM)&hdexItem);
    if (fCheckNotifies)
        ok(notifies_received(), "setItem(): not all expected notifies were received\n");
    return ret;
}