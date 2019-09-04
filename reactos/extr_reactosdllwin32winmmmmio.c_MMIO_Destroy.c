#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* lpNext; } ;
typedef  TYPE_1__* LPWINE_MMIO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__* MMIOList ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINMM_cs ; 

__attribute__((used)) static	BOOL		MMIO_Destroy(LPWINE_MMIO wm)
{
    LPWINE_MMIO*	m;

    EnterCriticalSection(&WINMM_cs);
    /* search for the matching one... */
    m = &MMIOList;
    while (*m && *m != wm) m = &(*m)->lpNext;
    /* ...and destroy */
    if (*m) {
	*m = (*m)->lpNext;
	HeapFree(GetProcessHeap(), 0, wm);
	wm = NULL;
    }
    LeaveCriticalSection(&WINMM_cs);
    return wm ? FALSE : TRUE;
}