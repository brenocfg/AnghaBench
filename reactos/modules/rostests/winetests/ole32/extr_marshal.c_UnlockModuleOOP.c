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
 int /*<<< orphan*/  CoReleaseServerProcess () ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cLocks ; 
 int /*<<< orphan*/  heventShutdown ; 

__attribute__((used)) static void UnlockModuleOOP(void)
{
    InterlockedDecrement(&cLocks); /* for test purposes only */
    if (!CoReleaseServerProcess())
        SetEvent(heventShutdown);
}