#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cchTextMax; int /*<<< orphan*/  pszText; void* mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  pszText; void* mask; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ HDITEMW ;
typedef  TYPE_2__ HDITEMA ;

/* Variables and functions */
 void* HDI_TEXT ; 
 int /*<<< orphan*/  HDM_SETITEMA ; 
 int /*<<< orphan*/  HDN_ITEMCHANGEDW ; 
 int /*<<< orphan*/  HDN_ITEMCHANGINGW ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  notifies_received () ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static LONG setItemUnicodeNotify(HWND hdex, int idx, LPSTR text, LPWSTR wText)
{
    LONG ret;
    HDITEMA hdexItem;
    HDITEMW hdexNotify;
    hdexItem.mask       = HDI_TEXT;
    hdexItem.pszText    = text;
    hdexItem.cchTextMax = 0;
    
    hdexNotify.mask    = HDI_TEXT;
    hdexNotify.pszText = wText;
    
    expect_notify(HDN_ITEMCHANGINGW, TRUE, (HDITEMA*)&hdexNotify);
    expect_notify(HDN_ITEMCHANGEDW, TRUE, (HDITEMA*)&hdexNotify);
    ret = SendMessageA(hdex, HDM_SETITEMA, idx, (LPARAM)&hdexItem);
    ok(notifies_received(), "setItemUnicodeNotify(): not all expected notifies were received\n");
    return ret;
}