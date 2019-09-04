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
typedef  size_t ULONG ;
typedef  scalar_t__ LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 scalar_t__* aszCommandLines ; 

LPSTR GetFromCommandLineHistory(ULONG ulCurrentCommandPos)
{
    LPSTR pRet;

    ENTER_FUNC();

    DPRINT((0,"GetFromCommandLineHistory(): current = %u\n",ulCurrentCommandPos));

    // skip leading ':'
    pRet = aszCommandLines[ulCurrentCommandPos] + 1;

    DPRINT((0,"GetFromCommandLineHistory(%s)\n",pRet));

    LEAVE_FUNC();

    return pRet;
}