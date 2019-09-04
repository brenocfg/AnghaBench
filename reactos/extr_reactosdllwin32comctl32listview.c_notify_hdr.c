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
struct TYPE_6__ {int /*<<< orphan*/  hwndNotify; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_5__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__* LPNMHDR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static LRESULT notify_hdr(const LISTVIEW_INFO *infoPtr, INT code, LPNMHDR pnmh)
{
    LRESULT result;
    
    TRACE("(code=%d)\n", code);

    pnmh->hwndFrom = infoPtr->hwndSelf;
    pnmh->idFrom = GetWindowLongPtrW(infoPtr->hwndSelf, GWLP_ID);
    pnmh->code = code;
    result = SendMessageW(infoPtr->hwndNotify, WM_NOTIFY, pnmh->idFrom, (LPARAM)pnmh);

    TRACE("  <= %ld\n", result);

    return result;
}