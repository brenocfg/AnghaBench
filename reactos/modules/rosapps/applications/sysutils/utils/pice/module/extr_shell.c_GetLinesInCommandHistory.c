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
typedef  int ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int LINES_IN_COMMAND_BUFFER ; 
 int ulCommandInPos ; 
 int ulCommandLastPos ; 

ULONG GetLinesInCommandHistory(void)
{
    ULONG ulResult = (ulCommandInPos-ulCommandLastPos)%LINES_IN_COMMAND_BUFFER;

    ENTER_FUNC();

    DPRINT((0,"GetLinesInCommandHistory() returns %u (ulIn %u ulLast %u)\n",ulResult,ulCommandInPos,ulCommandLastPos));

    LEAVE_FUNC();

    return ulResult;
}