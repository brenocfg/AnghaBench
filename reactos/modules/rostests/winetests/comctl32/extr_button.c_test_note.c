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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  BCM_GETNOTE ; 
 int /*<<< orphan*/  BCM_GETNOTELENGTH ; 
 int /*<<< orphan*/  BCM_SETNOTE ; 
 scalar_t__ BS_COMMANDLINK ; 
 scalar_t__ BS_DEFCOMMANDLINK ; 
 scalar_t__ BS_PUSHBUTTON ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_NOT_SUPPORTED ; 
 int GetLastError () ; 
 int NO_ERROR ; 
 int SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * create_button (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 scalar_t__ lstrlenW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_note(void)
{
    HWND hwnd;
    BOOL ret;
    WCHAR test_w[] = {'t', 'e', 's', 't', 0};
    WCHAR tes_w[] = {'t', 'e', 's', 0};
    WCHAR deadbeef_w[] = {'d', 'e', 'a', 'd', 'b', 'e', 'e', 'f', 0};
    WCHAR buffer_w[10];
    DWORD size;
    DWORD error;
    INT type;

    hwnd = create_button(BS_COMMANDLINK, NULL);
    ok(hwnd != NULL, "Expect hwnd not null\n");
    SetLastError(0xdeadbeef);
    size = ARRAY_SIZE(buffer_w);
    ret = SendMessageA(hwnd, BCM_GETNOTE, (WPARAM)&size, (LPARAM)buffer_w);
    error = GetLastError();
    if (!ret && error == 0xdeadbeef)
    {
        win_skip("BCM_GETNOTE message is unavailable. Skipping note tests\n"); /* xp or 2003 */
        DestroyWindow(hwnd);
        return;
    }
    DestroyWindow(hwnd);

    for (type = BS_PUSHBUTTON; type <= BS_DEFCOMMANDLINK; type++)
    {
        if (type == BS_DEFCOMMANDLINK || type == BS_COMMANDLINK)
        {
            hwnd = create_button(type, NULL);
            ok(hwnd != NULL, "Expect hwnd not null\n");

            /* Get note when note hasn't been not set yet */
            SetLastError(0xdeadbeef);
            lstrcpyW(buffer_w, deadbeef_w);
            size = ARRAY_SIZE(buffer_w);
            ret = SendMessageA(hwnd, BCM_GETNOTE, (WPARAM)&size, (LPARAM)buffer_w);
            error = GetLastError();
            ok(!ret, "Expect BCM_GETNOTE return false\n");
            ok(!lstrcmpW(buffer_w, deadbeef_w), "Expect note: %s, got: %s\n",
               wine_dbgstr_w(deadbeef_w), wine_dbgstr_w(buffer_w));
            ok(size == ARRAY_SIZE(buffer_w), "Got: %d\n", size);
            ok(error == ERROR_INVALID_PARAMETER, "Expect last error: 0x%08x, got: 0x%08x\n",
               ERROR_INVALID_PARAMETER, error);

            /* Get note length when note is not set */
            ret = SendMessageA(hwnd, BCM_GETNOTELENGTH, 0, 0);
            ok(ret == 0, "Expect note length: %d, got: %d\n", 0, ret);

            /* Successful set note, get note and get note length */
            SetLastError(0xdeadbeef);
            ret = SendMessageA(hwnd, BCM_SETNOTE, 0, (LPARAM)test_w);
            ok(ret, "Expect BCM_SETNOTE return true\n");
            error = GetLastError();
            ok(error == NO_ERROR, "Expect last error: 0x%08x, got: 0x%08x\n", NO_ERROR, error);

            SetLastError(0xdeadbeef);
            lstrcpyW(buffer_w, deadbeef_w);
            size = ARRAY_SIZE(buffer_w);
            ret = SendMessageA(hwnd, BCM_GETNOTE, (WPARAM)&size, (LPARAM)buffer_w);
            ok(ret, "Expect BCM_GETNOTE return true\n");
            ok(!lstrcmpW(buffer_w, test_w), "Expect note: %s, got: %s\n", wine_dbgstr_w(test_w),
               wine_dbgstr_w(buffer_w));
            ok(size == ARRAY_SIZE(buffer_w), "Got: %d\n", size);
            error = GetLastError();
            ok(error == NO_ERROR, "Expect last error: 0x%08x, got: 0x%08x\n", NO_ERROR, error);

            ret = SendMessageA(hwnd, BCM_GETNOTELENGTH, 0, 0);
            ok(ret == ARRAY_SIZE(test_w) - 1, "Got: %d\n", ret);

            /* Insufficient buffer, return partial string */
            SetLastError(0xdeadbeef);
            lstrcpyW(buffer_w, deadbeef_w);
            size = ARRAY_SIZE(test_w) - 1;
            ret = SendMessageA(hwnd, BCM_GETNOTE, (WPARAM)&size, (LPARAM)buffer_w);
            ok(!ret, "Expect BCM_GETNOTE return false\n");
            ok(!lstrcmpW(buffer_w, tes_w), "Expect note: %s, got: %s\n", wine_dbgstr_w(tes_w),
               wine_dbgstr_w(buffer_w));
            ok(size == ARRAY_SIZE(test_w), "Got: %d\n", size);
            error = GetLastError();
            ok(error == ERROR_INSUFFICIENT_BUFFER, "Expect last error: 0x%08x, got: 0x%08x\n",
               ERROR_INSUFFICIENT_BUFFER, error);

            /* Set note with NULL buffer */
            SetLastError(0xdeadbeef);
            ret = SendMessageA(hwnd, BCM_SETNOTE, 0, 0);
            ok(ret, "Expect BCM_SETNOTE return false\n");
            error = GetLastError();
            ok(error == NO_ERROR, "Expect last error: 0x%08x, got: 0x%08x\n", NO_ERROR, error);

            /* Check that set note with NULL buffer make note empty */
            SetLastError(0xdeadbeef);
            lstrcpyW(buffer_w, deadbeef_w);
            size = ARRAY_SIZE(buffer_w);
            ret = SendMessageA(hwnd, BCM_GETNOTE, (WPARAM)&size, (LPARAM)buffer_w);
            ok(ret, "Expect BCM_GETNOTE return true\n");
            ok(lstrlenW(buffer_w) == 0, "Expect note length 0\n");
            ok(size == ARRAY_SIZE(buffer_w), "Got: %d\n", size);
            error = GetLastError();
            ok(error == NO_ERROR, "Expect last error: 0x%08x, got: 0x%08x\n", NO_ERROR, error);
            ret = SendMessageA(hwnd, BCM_GETNOTELENGTH, 0, 0);
            ok(ret == 0, "Expect note length: %d, got: %d\n", 0, ret);

            /* Get note with NULL buffer */
            SetLastError(0xdeadbeef);
            size = ARRAY_SIZE(buffer_w);
            ret = SendMessageA(hwnd, BCM_GETNOTE, (WPARAM)&size, 0);
            ok(!ret, "Expect BCM_SETNOTE return false\n");
            ok(size == ARRAY_SIZE(buffer_w), "Got: %d\n", size);
            error = GetLastError();
            ok(error == ERROR_INVALID_PARAMETER, "Expect last error: 0x%08x, got: 0x%08x\n",
               ERROR_INVALID_PARAMETER, error);

            /* Get note with NULL size */
            SetLastError(0xdeadbeef);
            lstrcpyW(buffer_w, deadbeef_w);
            ret = SendMessageA(hwnd, BCM_GETNOTE, 0, (LPARAM)buffer_w);
            ok(!ret, "Expect BCM_SETNOTE return false\n");
            ok(!lstrcmpW(buffer_w, deadbeef_w), "Expect note: %s, got: %s\n",
               wine_dbgstr_w(deadbeef_w), wine_dbgstr_w(buffer_w));
            error = GetLastError();
            ok(error == ERROR_INVALID_PARAMETER, "Expect last error: 0x%08x, got: 0x%08x\n",
               ERROR_INVALID_PARAMETER, error);

            /* Get note with zero size */
            SetLastError(0xdeadbeef);
            size = 0;
            lstrcpyW(buffer_w, deadbeef_w);
            ret = SendMessageA(hwnd, BCM_GETNOTE, (WPARAM)&size, (LPARAM)buffer_w);
            ok(!ret, "Expect BCM_GETNOTE return false\n");
            ok(!lstrcmpW(buffer_w, deadbeef_w), "Expect note: %s, got: %s\n",
               wine_dbgstr_w(deadbeef_w), wine_dbgstr_w(buffer_w));
            ok(size == 1, "Got: %d\n", size);
            error = GetLastError();
            ok(error == ERROR_INSUFFICIENT_BUFFER, "Expect last error: 0x%08x, got: 0x%08x\n",
               ERROR_INSUFFICIENT_BUFFER, error);

            DestroyWindow(hwnd);
        }
        else
        {
            hwnd = create_button(type, NULL);
            ok(hwnd != NULL, "Expect hwnd not null\n");
            SetLastError(0xdeadbeef);
            size = ARRAY_SIZE(buffer_w);
            ret = SendMessageA(hwnd, BCM_GETNOTE, (WPARAM)&size, (LPARAM)buffer_w);
            ok(!ret, "Expect BCM_GETNOTE return false\n");
            error = GetLastError();
            ok(error == ERROR_NOT_SUPPORTED, "Expect last error: 0x%08x, got: 0x%08x\n",
               ERROR_NOT_SUPPORTED, error);
            DestroyWindow(hwnd);
        }
    }
}