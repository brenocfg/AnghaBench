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
typedef  int /*<<< orphan*/  test_progidW ;
typedef  int /*<<< orphan*/  test_iconW ;
struct assoc_getstring_test {scalar_t__ len; int flags; scalar_t__ hr; scalar_t__ brokenhr; int /*<<< orphan*/  str; scalar_t__ key; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  IQueryAssociations ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int ASSOCF_NONE ; 
 int ASSOCF_NOTRUNCATE ; 
 int /*<<< orphan*/  ASSOCSTR_DEFAULTICON ; 
 int /*<<< orphan*/  ASSOCSTR_EXECUTABLE ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_QueryAssociations ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/ * HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  IID_IQueryAssociations ; 
 scalar_t__ IQueryAssociations_GetString (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 scalar_t__ IQueryAssociations_Init (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IQueryAssociations_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  REG_SZ ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int broken (int) ; 
 int /*<<< orphan*/  getstring_test (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 struct assoc_getstring_test* getstring_tests ; 
 scalar_t__ httpW ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_IQueryAssociations_GetString(void)
{
    static WCHAR test_extensionW[] = {'.','t','e','s','t',0};
    static WCHAR test_progidW[] = {'t','e','s','t','f','i','l','e',0};
    static WCHAR DefaultIconW[] = {'D','e','f','a','u','l','t','I','c','o','n',0};
    /* folder.ico, why not */
    static WCHAR test_iconW[] = {'s','h','e','l','l','3','2','.','d','l','l',',','1',0};
    HKEY test_extension_key;
    HKEY test_progid_key;
    HKEY test_defaulticon_key;
    LRESULT r;

    struct assoc_getstring_test *ptr = getstring_tests;
    IQueryAssociations *assoc;
    HRESULT hr;
    DWORD len;
    int i = 0;

    r = RegCreateKeyExW(HKEY_CLASSES_ROOT, test_extensionW, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &test_extension_key, NULL);
    if (r == ERROR_ACCESS_DENIED)
    {
        win_skip("Not enough permissions to create a test key.\n");
        return;
    }

    ok(r == ERROR_SUCCESS, "RegCreateKeyExW(HKCR, \".test\") failed: 0x%lx\n", r);
    r = RegSetValueExW(test_extension_key, NULL, 0, REG_SZ, (PBYTE)test_progidW, sizeof(test_progidW));
    ok(r == ERROR_SUCCESS, "RegSetValueExW(HKCR\\.test, NULL, \"testfile\") failed: 0x%lx\n", r);

    /* adding progid key with no information should fail to return information */
    r = RegCreateKeyExW(HKEY_CLASSES_ROOT, test_progidW, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &test_progid_key, NULL);
    ok(r == ERROR_SUCCESS, "RegCreateKeyExW(HKCR, \"testfile\") failed: 0x%lx\n", r);
    getstring_test(test_extensionW, NULL, ASSOCSTR_DEFAULTICON, NULL, __LINE__);
    getstring_test(test_progidW, NULL, ASSOCSTR_DEFAULTICON, NULL, __LINE__);
    getstring_test(NULL, test_progid_key, ASSOCSTR_DEFAULTICON, NULL, __LINE__);

    /* adding information to the progid should return that information */
    r = RegCreateKeyExW(test_progid_key, DefaultIconW, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &test_defaulticon_key, NULL);
    ok(r == ERROR_SUCCESS, "RegCreateKeyExW(HKCR\\testfile\\DefaultIcon) failed: 0x%lx\n", r);
    r = RegSetValueExW(test_defaulticon_key, NULL, 0, REG_SZ, (PBYTE)test_iconW, sizeof(test_iconW));
    ok(r == ERROR_SUCCESS, "RegSetValueExW(HKCR\\testfile\\DefaultIcon, NULL, \"folder.ico\") failed: 0x%lx\n", r);
    getstring_test(test_extensionW, NULL, ASSOCSTR_DEFAULTICON, test_iconW, __LINE__);
    getstring_test(test_progidW, NULL, ASSOCSTR_DEFAULTICON, test_iconW, __LINE__);
    getstring_test(NULL, test_progid_key, ASSOCSTR_DEFAULTICON, test_iconW, __LINE__);

    RegDeleteKeyW(test_progid_key, DefaultIconW);
    RegDeleteKeyW(HKEY_CLASSES_ROOT, test_progidW);
    RegDeleteKeyW(HKEY_CLASSES_ROOT, test_extensionW);

    hr = CoCreateInstance(&CLSID_QueryAssociations, NULL, CLSCTX_INPROC_SERVER, &IID_IQueryAssociations, (void*)&assoc);
    ok(hr == S_OK, "failed to create object, 0x%x\n", hr);

    hr = IQueryAssociations_Init(assoc, ASSOCF_NONE, httpW, NULL, NULL);
    ok(hr == S_OK, "Init failed, 0x%x\n", hr);

    len = 0;
    hr = IQueryAssociations_GetString(assoc, ASSOCF_NONE, ASSOCSTR_EXECUTABLE, NULL, NULL, &len);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);
    ok(len > 0, "got wrong needed length, %d\n", len);

    while (ptr->key)
    {
        WCHAR buffW[MAX_PATH];
        DWORD len;

        hr = IQueryAssociations_Init(assoc, ASSOCF_NONE, ptr->key, NULL, NULL);
        ok(hr == S_OK, "%d: Init failed, 0x%x\n", i, hr);

        len = ptr->len;
        buffW[0] = ptr->flags & ASSOCF_NOTRUNCATE ? 0x1 : 0;
        hr = IQueryAssociations_GetString(assoc, ptr->flags, ptr->str, NULL, buffW, &len);
        if (hr != ptr->hr)
            ok(broken(hr == ptr->brokenhr), "%d: GetString failed, 0x%08x\n", i, hr);
        else
        {
            ok(hr == ptr->hr, "%d: GetString failed, 0x%08x\n", i, hr);
            ok(len > ptr->len, "%d: got needed length %d\n", i, len);
        }

        /* even with ASSOCF_NOTRUNCATE it's null terminated */
        if ((ptr->flags & ASSOCF_NOTRUNCATE) && (ptr->len > 0))
            ok(buffW[0] == 0 || broken(buffW[0] == 0x1) /* pre win7 */, "%d: got %x\n", i, buffW[0]);

        if (!(ptr->flags & ASSOCF_NOTRUNCATE) && ptr->len && FAILED(ptr->hr))
            ok(buffW[0] != 0, "%d: got %x\n", i, buffW[0]);

        i++;
        ptr++;
    }

    IQueryAssociations_Release(assoc);
}