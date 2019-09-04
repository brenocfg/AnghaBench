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
struct TYPE_5__ {scalar_t__ hmmio; } ;
struct TYPE_6__ {TYPE_1__ info; struct TYPE_6__* lpNext; } ;
typedef  TYPE_2__* LPWINE_MMIO ;
typedef  scalar_t__ HMMIO ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_2__* MMIOList ; 
 int /*<<< orphan*/  WINMM_cs ; 

__attribute__((used)) static LPWINE_MMIO      MMIO_Get(HMMIO h)
{
    LPWINE_MMIO		wm = NULL;

    EnterCriticalSection(&WINMM_cs);
    for (wm = MMIOList; wm; wm = wm->lpNext) {
	if (wm->info.hmmio == h)
	    break;
    }
    LeaveCriticalSection(&WINMM_cs);
    return wm;
}