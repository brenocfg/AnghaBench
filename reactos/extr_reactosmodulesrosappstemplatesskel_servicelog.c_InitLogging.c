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

/* Variables and functions */
 int /*<<< orphan*/  DeleteFile (int /*<<< orphan*/ ) ; 
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