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
typedef  char WCHAR ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 scalar_t__ HKEY_LOCAL_MACHINE ; 
 scalar_t__ INVALID_RUNCMD_RETURN ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegDeleteValueW (scalar_t__,char*) ; 
 scalar_t__ RegEnumValueW (scalar_t__,scalar_t__,char*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegOpenKeyExW (scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegQueryInfoKeyW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SM_CLEANBOOT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ runCmd (char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wprintf (char*,char*) ; 

__attribute__((used)) static BOOL ProcessRunKeys(HKEY hkRoot, LPCWSTR szKeyName, BOOL bDelete,
        BOOL bSynchronous)
{
    static const WCHAR WINKEY_NAME[]={'S','o','f','t','w','a','r','e','\\',
        'M','i','c','r','o','s','o','f','t','\\','W','i','n','d','o','w','s','\\',
        'C','u','r','r','e','n','t','V','e','r','s','i','o','n',0};
    HKEY hkWin=NULL, hkRun=NULL;
    LONG res=ERROR_SUCCESS;
    DWORD i, nMaxCmdLine=0, nMaxValue=0;
    WCHAR *szCmdLine=NULL;
    WCHAR *szValue=NULL;

    if (hkRoot==HKEY_LOCAL_MACHINE)
        wprintf(L"processing %s entries under HKLM\n", szKeyName);
    else
        wprintf(L"processing %s entries under HKCU\n", szKeyName);

    if ((res=RegOpenKeyExW(hkRoot, WINKEY_NAME, 0, KEY_READ, &hkWin))!=ERROR_SUCCESS)
    {
        printf("RegOpenKey failed on Software\\Microsoft\\Windows\\CurrentVersion (%ld)\n",
                res);

        goto end;
    }

    if ((res=RegOpenKeyExW(hkWin, szKeyName, 0, bDelete?KEY_ALL_ACCESS:KEY_READ, &hkRun))!=
            ERROR_SUCCESS)
    {
        if (res==ERROR_FILE_NOT_FOUND)
        {
            printf("Key doesn't exist - nothing to be done\n");

            res=ERROR_SUCCESS;
        }
        else
            printf("RegOpenKey failed on run key (%ld)\n", res);

        goto end;
    }

    if ((res=RegQueryInfoKeyW(hkRun, NULL, NULL, NULL, NULL, NULL, NULL, &i, &nMaxValue,
                    &nMaxCmdLine, NULL, NULL))!=ERROR_SUCCESS)
    {
        printf("Couldn't query key info (%ld)\n", res);

        goto end;
    }

    if (i==0)
    {
        printf("No commands to execute.\n");

        res=ERROR_SUCCESS;
        goto end;
    }

    if ((szCmdLine=malloc(nMaxCmdLine))==NULL)
    {
        printf("Couldn't allocate memory for the commands to be executed\n");

        res=ERROR_NOT_ENOUGH_MEMORY;
        goto end;
    }

    if ((szValue=malloc((++nMaxValue)*sizeof(*szValue)))==NULL)
    {
        printf("Couldn't allocate memory for the value names\n");

        free(szCmdLine);
        res=ERROR_NOT_ENOUGH_MEMORY;
        goto end;
    }

    while(i>0)
    {
        DWORD nValLength=nMaxValue, nDataLength=nMaxCmdLine;
        DWORD type;

        --i;

        if ((res=RegEnumValueW(hkRun, i, szValue, &nValLength, 0, &type,
                        (LPBYTE)szCmdLine, &nDataLength))!=ERROR_SUCCESS)
        {
            printf("Couldn't read in value %lu - %ld\n", i, res);

            continue;
        }

        /* safe mode - force to run if prefixed with asterisk */
        if (GetSystemMetrics(SM_CLEANBOOT) && (szValue[0] != L'*')) continue;

        if (bDelete && (res=RegDeleteValueW(hkRun, szValue))!=ERROR_SUCCESS)
        {
            printf("Couldn't delete value - %lu, %ld. Running command anyways.\n", i, res);
        }

        if (type!=REG_SZ)
        {
            printf("Incorrect type of value #%lu (%lu)\n", i, type);

            continue;
        }

        if ((res=runCmd(szCmdLine, NULL, bSynchronous, FALSE))==INVALID_RUNCMD_RETURN)
        {
            printf("Error running cmd #%lu (%ld)\n", i, GetLastError());
        }

        printf("Done processing cmd #%lu\n", i);
    }

    free(szValue);
    free(szCmdLine);
    res=ERROR_SUCCESS;

end:
    if (hkRun!=NULL)
        RegCloseKey(hkRun);
    if (hkWin!=NULL)
        RegCloseKey(hkWin);

    printf("done\n");

    return res==ERROR_SUCCESS?TRUE:FALSE;
}