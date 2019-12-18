#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  test_exe ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ reg_save_value ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  char* DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 char* ERROR_ACCESS_DENIED ; 
 char* ERROR_FILE_NOT_FOUND ; 
 char* ERROR_SUCCESS ; 
 scalar_t__ GetFileAttributesA (char*) ; 
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int MAX_PATH ; 
 char* REG_CREATED_NEW_KEY ; 
 int /*<<< orphan*/  REG_DWORD ; 
 char* REG_OPENED_EXISTING_KEY ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 char* RegCreateKeyA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* RegCreateKeyExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crash_and_debug (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  crash_and_winedbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 scalar_t__ pDebugActiveProcessStop ; 
 scalar_t__ pDebugSetProcessKillOnExit ; 
 int /*<<< orphan*/  restore_value (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  save_value (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  trace (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_ExitCode(void)
{
    static const char* AeDebug="Software\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug";
    static const char* WineDbg="Software\\Wine\\WineDbg";
    char test_exe[MAX_PATH];
    DWORD ret;
    HKEY hkey;
    DWORD disposition;
    reg_save_value auto_value;
    reg_save_value debugger_value;

    GetModuleFileNameA(GetModuleHandleA(NULL), test_exe, sizeof(test_exe));
    if (GetFileAttributesA(test_exe) == INVALID_FILE_ATTRIBUTES)
        strcat(test_exe, ".so");
    if (GetFileAttributesA(test_exe) == INVALID_FILE_ATTRIBUTES)
    {
        ok(0, "could not find the test executable '%s'\n", test_exe);
        return;
    }

    ret=RegCreateKeyExA(HKEY_LOCAL_MACHINE, AeDebug, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, &disposition);
    if (ret == ERROR_SUCCESS)
    {
        save_value(hkey, "auto", &auto_value);
        save_value(hkey, "debugger", &debugger_value);
        trace("HKLM\\%s\\debugger is set to '%s'\n", AeDebug, debugger_value.data);
    }
    else if (ret == ERROR_ACCESS_DENIED)
    {
        skip("not enough privileges to change the debugger\n");
        return;
    }
    else if (ret != ERROR_FILE_NOT_FOUND)
    {
        ok(0, "could not open the AeDebug key: %d\n", ret);
        return;
    }
    else debugger_value.data = NULL;

    if (debugger_value.data && debugger_value.type == REG_SZ &&
        strstr((char*)debugger_value.data, "winedbg --auto"))
    {
        HKEY hkeyWinedbg;
        ret=RegCreateKeyA(HKEY_CURRENT_USER, WineDbg, &hkeyWinedbg);
        if (ret == ERROR_SUCCESS)
        {
            static DWORD zero;
            reg_save_value crash_dlg_value;
            save_value(hkeyWinedbg, "ShowCrashDialog", &crash_dlg_value);
            RegSetValueExA(hkeyWinedbg, "ShowCrashDialog", 0, REG_DWORD, (BYTE *)&zero, sizeof(DWORD));
            crash_and_winedbg(hkey, test_exe);
            restore_value(hkeyWinedbg, &crash_dlg_value);
            RegCloseKey(hkeyWinedbg);
        }
        else
            ok(0, "Couldn't access WineDbg Key - error %u\n", ret);
    }

    if (winetest_interactive)
        /* Since the debugging process never sets the debug event, it isn't recognized
           as a valid debugger and, after the debugger exits, Windows will show a dialog box
           asking the user what to do */
        crash_and_debug(hkey, test_exe, "dbg,none");
    else
        skip("\"none\" debugger test needs user interaction\n");
    ok(disposition == REG_OPENED_EXISTING_KEY, "expected REG_OPENED_EXISTING_KEY, got %d\n", disposition);
    crash_and_debug(hkey, test_exe, "dbg,event,order");
    crash_and_debug(hkey, test_exe, "dbg,attach,event,code2");
    if (pDebugSetProcessKillOnExit)
        crash_and_debug(hkey, test_exe, "dbg,attach,event,nokill");
    else
        win_skip("DebugSetProcessKillOnExit is not available\n");
    if (pDebugActiveProcessStop)
        crash_and_debug(hkey, test_exe, "dbg,attach,event,detach");
    else
        win_skip("DebugActiveProcessStop is not available\n");

    if (disposition == REG_CREATED_NEW_KEY)
    {
        RegCloseKey(hkey);
        RegDeleteKeyA(HKEY_LOCAL_MACHINE, AeDebug);
    }
    else
    {
        restore_value(hkey, &auto_value);
        restore_value(hkey, &debugger_value);
        RegCloseKey(hkey);
    }
}