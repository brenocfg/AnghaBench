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
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int LOG_ERROR ; 
 int LOG_EVENTLOG ; 
 int /*<<< orphan*/  LogToEventLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ OpenLogFile () ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  hLogFile ; 
 int /*<<< orphan*/  lpLogFileName ; 

VOID
InitLogging()
{
    WCHAR wcBom = 0xFEFF;

    DeleteFile(lpLogFileName);

#ifdef _UNICODE
    if (OpenLogFile())
    {
        DWORD bytesWritten;

        WriteFile(hLogFile,
                  &wcBom,
                  sizeof(WCHAR),
                  &bytesWritten,
                  NULL);
        if (bytesWritten == 0)
        {
            LogToEventLog(_T("Failed to write to log file"),
                          GetLastError(),
                          0,
                          LOG_EVENTLOG | LOG_ERROR);
        }

        CloseHandle(hLogFile);
    }
#endif
}