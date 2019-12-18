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
struct op_mask {scalar_t__ startup; scalar_t__ postlogin; scalar_t__ prelogin; int /*<<< orphan*/  ntonly; scalar_t__ preboot; int /*<<< orphan*/  w9xonly; } ;
typedef  int /*<<< orphan*/  gen_path ;
typedef  char TCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 struct op_mask DEFAULT ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowsDirectory (char*,int) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int MAX_PATH ; 
 scalar_t__ ProcessRunKeys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ REG_OPENED_EXISTING_KEY ; 
 int /*<<< orphan*/  REG_OPTION_VOLATILE ; 
 size_t RUNKEY_RUN ; 
 size_t RUNKEY_RUNONCE ; 
 size_t RUNKEY_RUNSERVICES ; 
 size_t RUNKEY_RUNSERVICESONCE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 struct op_mask SESSION_START ; 
 struct op_mask SETUP ; 
 int /*<<< orphan*/  SHCreateSessionKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SM_CLEANBOOT ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCurrentDirectory (char*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ pendingRename () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * runkeys_names ; 
 scalar_t__ wininit () ; 
 int /*<<< orphan*/  wprintf (char*,char*,int /*<<< orphan*/ ) ; 

int startup(int argc, const char *argv[])
{
    struct op_mask ops; /* Which of the ops do we want to perform? */
    /* First, set the current directory to SystemRoot */
    TCHAR gen_path[MAX_PATH];
    DWORD res;
    HKEY hSessionKey, hKey;
    HRESULT hr;

    res = GetWindowsDirectory(gen_path, sizeof(gen_path));

    if (res==0)
    {
		printf("Couldn't get the windows directory - error %ld\n",
			GetLastError());

		return 100;
    }

    if (!SetCurrentDirectory(gen_path))
    {
        wprintf(L"Cannot set the dir to %s (%ld)\n", gen_path, GetLastError());

        return 100;
    }

    hr = SHCreateSessionKey(KEY_WRITE, &hSessionKey);
    if (SUCCEEDED(hr))
    {
        LONG Error;
        DWORD dwDisp;

        Error = RegCreateKeyEx(hSessionKey, L"StartupHasBeenRun", 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, &dwDisp);
        RegCloseKey(hSessionKey);
        if (Error == ERROR_SUCCESS)
        {
            RegCloseKey(hKey);
            if (dwDisp == REG_OPENED_EXISTING_KEY)
            {
                /* Startup programs has already been run */
                return 0;
            }
        }
    }

    if (argc > 1)
    {
        switch(argv[1][0])
        {
        case 'r': /* Restart */
            ops = SETUP;
            break;
        case 's': /* Full start */
            ops = SESSION_START;
            break;
        default:
            ops = DEFAULT;
            break;
        }
    } else
        ops = DEFAULT;

    /* do not run certain items in Safe Mode */
    if(GetSystemMetrics(SM_CLEANBOOT)) ops.startup = FALSE;

    /* Perform the ops by order, stopping if one fails, skipping if necessary */
    /* Shachar: Sorry for the perl syntax */
    res = TRUE;
    if (res && !ops.ntonly && ops.preboot)
         res = wininit();
    if (res && !ops.w9xonly && ops.preboot)
         res = pendingRename();
    if (res && !ops.ntonly && ops.prelogin)
         res = ProcessRunKeys(HKEY_LOCAL_MACHINE, runkeys_names[RUNKEY_RUNSERVICESONCE], TRUE, FALSE);
    if (res && !ops.ntonly && ops.prelogin && ops.startup)
         res = ProcessRunKeys(HKEY_LOCAL_MACHINE, runkeys_names[RUNKEY_RUNSERVICES], FALSE, FALSE);
    if (res && ops.postlogin)
         res = ProcessRunKeys(HKEY_LOCAL_MACHINE, runkeys_names[RUNKEY_RUNONCE], TRUE, TRUE);
    if (res && ops.postlogin && ops.startup)
         res = ProcessRunKeys(HKEY_LOCAL_MACHINE, runkeys_names[RUNKEY_RUN], FALSE, FALSE);
    if (res && ops.postlogin && ops.startup)
         res = ProcessRunKeys(HKEY_CURRENT_USER, runkeys_names[RUNKEY_RUN], FALSE, FALSE);
    if (res && ops.postlogin && ops.startup)
         res = ProcessRunKeys(HKEY_CURRENT_USER, runkeys_names[RUNKEY_RUNONCE], TRUE, FALSE);

    printf("Operation done\n");

    return res ? 0 : 101;
}