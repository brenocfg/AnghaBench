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
typedef  char* UINT ;
typedef  int MSIINSTALLCONTEXT ;
typedef  char* LPSTR ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 char* ERROR_INVALID_PARAMETER ; 
 char* ERROR_NO_MORE_ITEMS ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 scalar_t__ MSIINSTALLCONTEXT_ALL ; 
 scalar_t__ MSIINSTALLCONTEXT_MACHINE ; 
 scalar_t__ MSIINSTALLCONTEXT_USERUNMANAGED ; 
 scalar_t__ MSIPATCHSTATE_ALL ; 
 scalar_t__ MSIPATCHSTATE_INVALID ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 char* get_user_sid () ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* pMsiEnumPatchesExA (char*,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,char*,char*,int*,char*,int*) ; 
 int /*<<< orphan*/  test_MsiEnumPatchesEx_machine () ; 
 int /*<<< orphan*/  test_MsiEnumPatchesEx_usermanaged (char*,char*) ; 
 int /*<<< orphan*/  test_MsiEnumPatchesEx_userunmanaged (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_MsiEnumPatchesEx(void)
{
    CHAR targetsid[MAX_PATH], targetprod[MAX_PATH];
    CHAR prodcode[MAX_PATH], prod_squashed[MAX_PATH];
    CHAR patchcode[MAX_PATH];
    MSIINSTALLCONTEXT context;
    LPSTR usersid;
    DWORD size;
    UINT r;

    if (!pMsiEnumPatchesExA)
    {
        win_skip("MsiEnumPatchesExA not implemented\n");
        return;
    }

    create_test_guid(prodcode, prod_squashed);
    usersid = get_user_sid();

    /* empty szProductCode */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA("", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                           MSIPATCHSTATE_ALL, 0, patchcode, targetprod, &context,
                           targetsid, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* garbage szProductCode */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA("garbage", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                           MSIPATCHSTATE_ALL, 0, patchcode, targetprod, &context,
                           targetsid, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* guid without brackets */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA("6700E8CF-95AB-4D9C-BC2C-15840DEA7A5D", usersid,
                           MSIINSTALLCONTEXT_USERUNMANAGED, MSIPATCHSTATE_ALL,
                           0, patchcode, targetprod, &context,
                           targetsid, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* guid with brackets */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA("{6700E8CF-95AB-4D9C-BC2C-15840DDA7A5D}", usersid,
                           MSIINSTALLCONTEXT_USERUNMANAGED, MSIPATCHSTATE_ALL,
                           0, patchcode, targetprod, &context,
                           targetsid, &size);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* szUserSid is S-1-5-18 */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, "S-1-5-18",
                           MSIINSTALLCONTEXT_USERUNMANAGED, MSIPATCHSTATE_ALL,
                           0, patchcode, targetprod, &context,
                           targetsid, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* dwContext is MSIINSTALLCONTEXT_MACHINE, but szUserSid is non-NULL */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_MACHINE,
                           MSIPATCHSTATE_ALL, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* dwContext is out of bounds */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, 0,
                           MSIPATCHSTATE_ALL, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* dwContext is out of bounds */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_ALL + 1,
                           MSIPATCHSTATE_ALL, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* dwFilter is out of bounds */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                           MSIPATCHSTATE_INVALID, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* dwFilter is out of bounds */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    size = MAX_PATH;
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                           MSIPATCHSTATE_ALL + 1, 0, patchcode, targetprod,
                           &context, targetsid, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* pcchTargetUserSid is NULL while szTargetUserSid is non-NULL */
    lstrcpyA(patchcode, "apple");
    lstrcpyA(targetprod, "banana");
    context = 0xdeadbeef;
    lstrcpyA(targetsid, "kiwi");
    r = pMsiEnumPatchesExA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                           MSIPATCHSTATE_ALL, 0, patchcode, targetprod,
                           &context, targetsid, NULL);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(patchcode, "apple"),
       "Expected patchcode to be unchanged, got %s\n", patchcode);
    ok(!lstrcmpA(targetprod, "banana"),
       "Expected targetprod to be unchanged, got %s\n", targetprod);
    ok(context == 0xdeadbeef,
       "Expected context to be unchanged, got %d\n", context);
    ok(!lstrcmpA(targetsid, "kiwi"),
       "Expected targetsid to be unchanged, got %s\n", targetsid);

    test_MsiEnumPatchesEx_usermanaged(usersid, usersid);
    test_MsiEnumPatchesEx_usermanaged(NULL, usersid);
    test_MsiEnumPatchesEx_usermanaged("S-1-2-34", "S-1-2-34");
    test_MsiEnumPatchesEx_userunmanaged(usersid, usersid);
    test_MsiEnumPatchesEx_userunmanaged(NULL, usersid);
    /* FIXME: Successfully test userunmanaged with a different user */
    test_MsiEnumPatchesEx_machine();
    LocalFree(usersid);
}