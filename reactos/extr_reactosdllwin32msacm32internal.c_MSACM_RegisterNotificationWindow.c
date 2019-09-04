#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINE_ACMNOTIFYWND ;
struct TYPE_7__ {scalar_t__ pACMDriverID; int /*<<< orphan*/  dwType; } ;
struct TYPE_8__ {struct TYPE_8__* pNextACMNotifyWnd; struct TYPE_8__* pPrevACMNotifyWnd; scalar_t__ fdwSupport; int /*<<< orphan*/  dwNotifyMsg; int /*<<< orphan*/  hNotifyWnd; TYPE_1__ obj; } ;
typedef  TYPE_2__* PWINE_ACMNOTIFYWND ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSACM_hHeap ; 
 TYPE_2__* MSACM_pFirstACMNotifyWnd ; 
 TYPE_2__* MSACM_pLastACMNotifyWnd ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_ACMOBJ_NOTIFYWND ; 

PWINE_ACMNOTIFYWND MSACM_RegisterNotificationWindow(HWND hNotifyWnd, DWORD dwNotifyMsg)
{
    PWINE_ACMNOTIFYWND	panwnd;

    TRACE("(%p,0x%08x)\n", hNotifyWnd, dwNotifyMsg);

    panwnd = HeapAlloc(MSACM_hHeap, 0, sizeof(WINE_ACMNOTIFYWND));
    panwnd->obj.dwType = WINE_ACMOBJ_NOTIFYWND;
    panwnd->obj.pACMDriverID = 0;
    panwnd->hNotifyWnd = hNotifyWnd;
    panwnd->dwNotifyMsg = dwNotifyMsg;
    panwnd->fdwSupport = 0;
    
    panwnd->pNextACMNotifyWnd = NULL;
    panwnd->pPrevACMNotifyWnd = MSACM_pLastACMNotifyWnd;
    if (MSACM_pLastACMNotifyWnd)
        MSACM_pLastACMNotifyWnd->pNextACMNotifyWnd = panwnd;
    MSACM_pLastACMNotifyWnd = panwnd;
    if (!MSACM_pFirstACMNotifyWnd)
        MSACM_pFirstACMNotifyWnd = panwnd;

    return panwnd;
}