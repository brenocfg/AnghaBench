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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConsoleReattach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetConsoleActiveScreenBuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID SetActiveScreenBuffer(HANDLE ScreenBuffer)
{
    ASSERT(ScreenBuffer);

    /* Set the active buffer and reattach the VDM UI to it */
    SetConsoleActiveScreenBuffer(ScreenBuffer);
    ConsoleReattach(ScreenBuffer);
}