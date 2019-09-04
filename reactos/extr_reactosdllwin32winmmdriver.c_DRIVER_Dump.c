#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static void DRIVER_Dump(const char *comment)
{
#if 0
    LPWINE_DRIVER 	lpDrv;

    TRACE("%s\n", comment);

    EnterCriticalSection( &mmdriver_lock );

    for (lpDrv = lpDrvItemList; lpDrv != NULL; lpDrv = lpDrv->lpNextItem)
    {
        TRACE("%p, magic %04lx, id %p, next %p\n", lpDrv, lpDrv->dwMagic, lpDrv->d.d32.dwDriverID, lpDrv->lpNextItem);
    }

    LeaveCriticalSection( &mmdriver_lock );
#endif
}