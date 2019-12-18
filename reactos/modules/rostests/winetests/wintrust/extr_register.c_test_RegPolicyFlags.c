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
typedef  int /*<<< orphan*/  flags1 ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pWintrustGetRegPolicyFlags (int*) ; 
 int /*<<< orphan*/  pWintrustSetRegPolicyFlags (int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RegPolicyFlags(void)
{
    /* Default state value 0x00023c00, which is
     *  WTPF_IGNOREREVOCATIONONTS |
     *  WTPF_OFFLINEOKNBU_COM |
     *  WTPF_OFFLINEOKNBU_IND |
     *  WTPF_OFFLINEOK_COM |
     *  WTPF_OFFLINEOK_IND
     */
    static const CHAR Software_Publishing[] =
     "Software\\Microsoft\\Windows\\CurrentVersion\\Wintrust\\"
     "Trust Providers\\Software Publishing";
    static const CHAR State[] = "State";
    HKEY key;
    LONG r;
    DWORD flags1, flags2, flags3, size;
    BOOL ret;

    if (!pWintrustGetRegPolicyFlags || !pWintrustSetRegPolicyFlags)
    {
        win_skip("Policy flags functions not present\n");
        return;
    }

    pWintrustGetRegPolicyFlags(&flags2);

    r = RegOpenKeyExA(HKEY_CURRENT_USER, Software_Publishing, 0, KEY_ALL_ACCESS,
     &key);
    ok(!r, "RegOpenKeyEx failed: %d\n", r);

    size = sizeof(flags1);
    r = RegQueryValueExA(key, State, NULL, NULL, (LPBYTE)&flags1, &size);
    ok(!r || r == ERROR_FILE_NOT_FOUND, "RegQueryValueEx failed: %d\n", r);
    if (!r)
        ok(flags1 == flags2, "Got %08x flags instead of %08x\n", flags1, flags2);

    flags3 = flags2 | 1;
    ret = pWintrustSetRegPolicyFlags(flags3);
    ok(ret, "WintrustSetRegPolicyFlags failed: %d\n", GetLastError());
    size = sizeof(flags1);
    r = RegQueryValueExA(key, State, NULL, NULL, (LPBYTE)&flags1, &size);
    ok(!r, "RegQueryValueEx failed: %d\n", r);
    ok(flags1 == flags3, "Got %08x flags instead of %08x\n", flags1, flags3);

    pWintrustSetRegPolicyFlags(flags2);

    RegCloseKey(key);
}