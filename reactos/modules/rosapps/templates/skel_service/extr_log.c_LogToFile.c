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
typedef  int UINT ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/ * LPCTSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExitProcess (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_END ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FormatMessage (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int LOG_ERROR ; 
 int LOG_EVENTLOG ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogToEventLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenLogFile () ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SetFilePointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _sntprintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int _tcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hLogFile ; 

__attribute__((used)) static BOOL
LogToFile(LPCTSTR lpMsg,
          DWORD errNum,
          DWORD exitCode,
          UINT flags)
{
    LPTSTR lpFullMsg = NULL;
    DWORD msgLen;

    if (!OpenLogFile())
        return FALSE;

    msgLen = _tcslen(lpMsg) + 1;

    if (flags & LOG_ERROR)
    {
        LPVOID lpSysMsg;
        DWORD eMsgLen;

        eMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                                NULL,
                                errNum,
                                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                (LPTSTR)&lpSysMsg,
                                0,
                                NULL);

        msgLen = msgLen + eMsgLen + 40;

        lpFullMsg = HeapAlloc(GetProcessHeap(),
                              0,
                              msgLen * sizeof(TCHAR));
        if (lpFullMsg)
        {
            _sntprintf(lpFullMsg,
                       msgLen,
                       _T("%s : %s\tErrNum = %lu ExitCode = %lu\r\n"),
                       lpMsg,
                       lpSysMsg,
                       errNum,
                       exitCode);
        }

        LocalFree(lpSysMsg);

    }
    else
    {
        msgLen += 2;

        lpFullMsg = HeapAlloc(GetProcessHeap(),
                              0,
                              msgLen * sizeof(TCHAR));
        if (lpFullMsg)
        {
            _sntprintf(lpFullMsg,
                       msgLen,
                      _T("%s\r\n"),
                      lpMsg);
        }
    }

    if (lpFullMsg)
    {
        DWORD bytesWritten;

        SetFilePointer(hLogFile, 0, NULL, FILE_END);

        WriteFile(hLogFile,
                  lpFullMsg,
                  _tcslen(lpFullMsg) * sizeof(TCHAR),
                  &bytesWritten,
                  NULL);
        if (bytesWritten == 0)
        {
            LogToEventLog(_T("Failed to write to log file"),
                          GetLastError(),
                          0,
                          LOG_EVENTLOG | LOG_ERROR);
        }

        HeapFree(GetProcessHeap(),
                 0,
                 lpFullMsg);
    }

    CloseHandle(hLogFile);

    if (exitCode > 0)
        ExitProcess(exitCode);
}