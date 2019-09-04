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
typedef  scalar_t__ LONG ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOCSTR_EXECUTABLE ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHDeleteKeyA (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  expect_hr (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lstrlenA (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 scalar_t__ pAssocQueryStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*,char*,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/ * strstr (char*,char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_getstring_no_extra(void)
{
    LONG ret;
    HKEY hkey;
    HRESULT hr;
    static const CHAR dotWinetest[] = {
        '.','w','i','n','e','t','e','s','t',0
    };
    static const CHAR winetestfile[] = {
        'w','i','n','e','t','e','s','t', 'f','i','l','e',0
    };
    static const CHAR winetestfileAction[] = {
        'w','i','n','e','t','e','s','t','f','i','l','e',
        '\\','s','h','e','l','l',
        '\\','f','o','o',
        '\\','c','o','m','m','a','n','d',0
    };
    static const CHAR action[] = {
        'n','o','t','e','p','a','d','.','e','x','e',0
    };
    CHAR buf[MAX_PATH];
    DWORD len = MAX_PATH;

    if (!pAssocQueryStringA)
    {
        win_skip("AssocQueryStringA() is missing\n");
        return;
    }

    buf[0] = '\0';
    ret = RegCreateKeyA(HKEY_CLASSES_ROOT, dotWinetest, &hkey);
    if (ret != ERROR_SUCCESS) {
        skip("failed to create dotWinetest key\n");
        return;
    }

    ret = RegSetValueA(hkey, NULL, REG_SZ, winetestfile, lstrlenA(winetestfile));
    RegCloseKey(hkey);
    if (ret != ERROR_SUCCESS)
    {
        skip("failed to set dotWinetest key\n");
        goto cleanup;
    }

    ret = RegCreateKeyA(HKEY_CLASSES_ROOT, winetestfileAction, &hkey);
    if (ret != ERROR_SUCCESS)
    {
        skip("failed to create winetestfileAction key\n");
        goto cleanup;
    }

    ret = RegSetValueA(hkey, NULL, REG_SZ, action, lstrlenA(action));
    RegCloseKey(hkey);
    if (ret != ERROR_SUCCESS)
    {
        skip("failed to set winetestfileAction key\n");
        goto cleanup;
    }

    hr = pAssocQueryStringA(0, ASSOCSTR_EXECUTABLE, dotWinetest, NULL, buf, &len);
    ok(hr == S_OK ||
       hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), /* XP and W2K3 */
       "Unexpected result : %08x\n", hr);
    hr = pAssocQueryStringA(0, ASSOCSTR_EXECUTABLE, dotWinetest, "foo", buf, &len);
    expect_hr(S_OK, hr);
    ok(strstr(buf, action) != NULL,
        "got '%s' (Expected result to include 'notepad.exe')\n", buf);

cleanup:
    SHDeleteKeyA(HKEY_CLASSES_ROOT, dotWinetest);
    SHDeleteKeyA(HKEY_CLASSES_ROOT, winetestfile);

}