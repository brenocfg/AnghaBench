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
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIME_MMTimeStop () ; 
 int /*<<< orphan*/  WINMM_cs ; 
 int /*<<< orphan*/  psLastEvent ; 
 int /*<<< orphan*/  psStopEvent ; 

__attribute__((used)) static	void WINMM_DeleteIData(void)
{
    TIME_MMTimeStop();

    /* FIXME: should also free content and resources allocated
     * inside WINMM_IData */
    CloseHandle(psStopEvent);
    CloseHandle(psLastEvent);
    DeleteCriticalSection(&WINMM_cs);
}