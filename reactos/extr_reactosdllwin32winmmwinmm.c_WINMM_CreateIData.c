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
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 void* CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINMM_cs ; 
 int /*<<< orphan*/  hWinMM32Instance ; 
 void* psLastEvent ; 
 void* psStopEvent ; 

__attribute__((used)) static	BOOL	WINMM_CreateIData(HINSTANCE hInstDLL)
{
    hWinMM32Instance = hInstDLL;
    psStopEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
    psLastEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
    InitializeCriticalSection(&WINMM_cs);
    return TRUE;
}