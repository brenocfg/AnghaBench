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
typedef  int /*<<< orphan*/  DEBUGGER_STATUS_BLOCK ;

/* Variables and functions */
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  PICE_IOCTL_STATUS ; 
 int /*<<< orphan*/  close_debugger () ; 
 int /*<<< orphan*/  debugger_file ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ open_debugger () ; 

void showstatus(void)
{
    DEBUGGER_STATUS_BLOCK sb;
    int iRetVal;

	if(open_debugger() != INVALID_HANDLE_VALUE)
	{
		iRetVal = ioctl(debugger_file,PICE_IOCTL_STATUS,&sb);

        //printf("LOADER: Test = %X\n",sb.Test);
		close_debugger();
	}
}