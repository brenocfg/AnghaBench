#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* pPrevACMNotifyWnd; struct TYPE_8__* pNextACMNotifyWnd; } ;
typedef  TYPE_1__ WINE_ACMNOTIFYWND ;
typedef  TYPE_1__ const* PWINE_ACMNOTIFYWND ;

/* Variables and functions */
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  MSACM_hHeap ; 
 TYPE_1__ const* MSACM_pFirstACMNotifyWnd ; 
 TYPE_1__ const* MSACM_pLastACMNotifyWnd ; 

PWINE_ACMNOTIFYWND MSACM_UnRegisterNotificationWindow(const WINE_ACMNOTIFYWND *panwnd)
{
    PWINE_ACMNOTIFYWND p;

    for (p = MSACM_pFirstACMNotifyWnd; p; p = p->pNextACMNotifyWnd) {
        if (p == panwnd) {
            PWINE_ACMNOTIFYWND pNext = p->pNextACMNotifyWnd;

            if (p->pPrevACMNotifyWnd) p->pPrevACMNotifyWnd->pNextACMNotifyWnd = p->pNextACMNotifyWnd;
            if (p->pNextACMNotifyWnd) p->pNextACMNotifyWnd->pPrevACMNotifyWnd = p->pPrevACMNotifyWnd;
            if (MSACM_pFirstACMNotifyWnd == p) MSACM_pFirstACMNotifyWnd = p->pNextACMNotifyWnd;
            if (MSACM_pLastACMNotifyWnd == p) MSACM_pLastACMNotifyWnd = p->pPrevACMNotifyWnd;
            HeapFree(MSACM_hHeap, 0, p);
            
            return pNext;
        }
    }
    return NULL;
}