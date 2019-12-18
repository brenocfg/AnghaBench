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
typedef  int UINT ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int LOG_ERROR ; 
 int LOG_EVENTLOG ; 
 int LOG_FILE ; 
 int /*<<< orphan*/  LogToEventLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LogToFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

VOID
LogEvent(LPCTSTR lpMsg,
         DWORD errNum,
         DWORD exitCode,
         UINT flags)
{
#ifdef DEBUG
    if (flags & LOG_FILE || flags & LOG_ERROR)
        LogToFile(lpMsg, errNum, exitCode, flags);
#endif
    if (flags & LOG_EVENTLOG)
        LogToEventLog(lpMsg, errNum, exitCode, flags);
}