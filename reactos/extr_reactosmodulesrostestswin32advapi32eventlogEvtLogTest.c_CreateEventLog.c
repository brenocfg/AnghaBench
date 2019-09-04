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
typedef  int /*<<< orphan*/  i ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  MaxSize ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_CREATE_SUB_KEY ; 
 int KEY_QUERY_VALUE ; 
 int KEY_SET_VALUE ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegFlushKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

BOOL CreateEventLog(LPCWSTR EventLogName,
                    UINT MaxSize,
                    UINT SourcesCount,
                    LPCWSTR EventLogSources[])
{
    BOOL Success = FALSE;
    LONG lRet;
    HKEY hKey = NULL, hEventKey = NULL, hSrcKey = NULL;
    UINT i;
    // WCHAR evtFile[] = L"D:\\myfile.evtx";

    wprintf(L"Creating log %s of MaxSize 0x%x with %d sources...", EventLogName, MaxSize, SourcesCount);

    lRet = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                         L"SYSTEM\\CurrentControlSet\\Services\\Eventlog",
                         0, KEY_CREATE_SUB_KEY,
                         &hKey);
    if (lRet != ERROR_SUCCESS)
        goto Quit;

    /*
     * At this precise moment, EventLog detects we create a new log registry key
     * and therefore creates for us the log file in System32\config (<= Win2k3)
     * or in System32\winevt\Logs (>= Vista).
     */
    lRet = RegCreateKeyExW(hKey,
                           EventLogName,
                           0, NULL, REG_OPTION_NON_VOLATILE,
                           KEY_CREATE_SUB_KEY | KEY_SET_VALUE, NULL,
                           &hEventKey, NULL);
    if (lRet != ERROR_SUCCESS)
        goto Quit;

    RegSetValueExW(hEventKey, L"MaxSize", 0, REG_DWORD,
                   (LPBYTE)&MaxSize, sizeof(MaxSize));

    i = 0;
    RegSetValueExW(hEventKey, L"Retention", 0, REG_DWORD,
                   (LPBYTE)&i, sizeof(i));

#if 0
    /*
     * Set the flag that will allow EventLog to use an alternative log file name.
     * If this flag is not set, EventLog will not care about the "File" value.
     * When the flag is set, EventLog monitors for the "File" value, which can be
     * changed at run-time, in which case a new event log file is created.
     */
    i = 1;
    RegSetValueExW(hEventKey, L"Flags", 0, REG_DWORD,
                   (LPBYTE)&i, sizeof(i));

    RegSetValueExW(hEventKey, L"File", 0, REG_EXPAND_SZ,
                   (LPBYTE)evtFile, sizeof(evtFile));
#endif

    for (i = 0; i < SourcesCount; i++)
    {
        lRet = RegCreateKeyExW(hEventKey,
                               EventLogSources[i],
                               0, NULL, REG_OPTION_NON_VOLATILE,
                               KEY_QUERY_VALUE, NULL,
                               &hSrcKey, NULL);
        RegFlushKey(hSrcKey);
        RegCloseKey(hSrcKey);
    }

    RegFlushKey(hEventKey);

    Success = TRUE;

Quit:
    if (Success)
        wprintf(L"Success\n");
    else
        wprintf(L"Failure\n");

    if (hEventKey)
        RegCloseKey(hEventKey);

    if (hKey)
        RegCloseKey(hKey);

    return Success;
}