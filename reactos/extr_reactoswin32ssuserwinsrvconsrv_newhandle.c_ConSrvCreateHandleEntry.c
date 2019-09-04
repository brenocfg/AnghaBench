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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PCONSOLE_IO_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustHandleCounts (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VOID
ConSrvCreateHandleEntry(PCONSOLE_IO_HANDLE Entry)
{
    /// LOCK /// PCONSOLE_IO_OBJECT Object = Entry->Object;
    /// LOCK /// EnterCriticalSection(&Object->Console->Lock);
    AdjustHandleCounts(Entry, +1);
    /// LOCK /// LeaveCriticalSection(&Object->Console->Lock);
}