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
typedef  int /*<<< orphan*/  prompt ;
typedef  int /*<<< orphan*/  label ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int ERROR_BAD_CONFIGURATION ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int ERROR_UNKNOWN_PRODUCT ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int MAX_PATH ; 
 int MSICODE_PRODUCT ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_MACHINE ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERMANAGED ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERUNMANAGED ; 
 int MSISOURCETYPE_NETWORK ; 
 int MSISOURCETYPE_URL ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* get_user_sid () ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pMsiSourceListEnumMediaDisksA (char*,char*,int /*<<< orphan*/ ,int,int,int*,char*,int*,char*,int*) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_MsiSourceListEnumMediaDisks(void)
{
    CHAR prodcode[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    CHAR keypath[MAX_PATH*2];
    CHAR label[MAX_PATH];
    CHAR prompt[MAX_PATH];
    HKEY prodkey, userkey, media, source;
    DWORD labelsz, promptsz, val, id;
    LPSTR usersid;
    LONG res;
    UINT r;
    REGSAM access = KEY_ALL_ACCESS;

    if (!pMsiSourceListEnumMediaDisksA)
    {
        win_skip("MsiSourceListEnumMediaDisksA is not available\n");
        return;
    }

    create_test_guid(prodcode, prod_squashed);
    if (!(usersid = get_user_sid()))
    {
        skip("User SID not available -> skipping MsiSourceListEnumMediaDisksA tests\n");
        return;
    }

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    /* GetLastError is not set by the function */

    /* NULL szProductCodeOrPatchCode */
    labelsz = sizeof(label);
    promptsz = sizeof(prompt);
    r = pMsiSourceListEnumMediaDisksA(NULL, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* empty szProductCodeOrPatchCode */
    labelsz = sizeof(label);
    promptsz = sizeof(prompt);
    r = pMsiSourceListEnumMediaDisksA("", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* garbage szProductCodeOrPatchCode */
    labelsz = sizeof(label);
    promptsz = sizeof(prompt);
    r = pMsiSourceListEnumMediaDisksA("garbage", usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* guid without brackets */
    labelsz = sizeof(label);
    promptsz = sizeof(prompt);
    r = pMsiSourceListEnumMediaDisksA("51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA",
                                      usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* guid with brackets */
    labelsz = sizeof(label);
    promptsz = sizeof(prompt);
    r = pMsiSourceListEnumMediaDisksA("{51CD2AD5-0482-4C46-8DDD-0ED1022AA1AA}",
                                      usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_UNKNOWN_PRODUCT,
       "Expected ERROR_UNKNOWN_PRODUCT, got %d\n", r);

    /* dwOptions has MSISOURCETYPE_NETWORK */
    labelsz = sizeof(label);
    promptsz = sizeof(prompt);
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT | MSISOURCETYPE_NETWORK,
                                      0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* dwOptions has MSISOURCETYPE_URL */
    labelsz = sizeof(label);
    promptsz = sizeof(prompt);
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT | MSISOURCETYPE_URL,
                                      0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* dwIndex is non-zero */
    labelsz = sizeof(label);
    promptsz = sizeof(prompt);
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 1, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);

    /* MSIINSTALLCONTEXT_USERUNMANAGED */

    lstrcpyA(keypath, "Software\\Microsoft\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyA(HKEY_CURRENT_USER, keypath, &userkey);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* user product key exists */
    labelsz = sizeof(label);
    promptsz = sizeof(prompt);
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyA(userkey, "SourceList", &source);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = 0xdeadbeef;
    lstrcpyA(prompt, "bbb");
    promptsz = 0xdeadbeef;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", promptsz);

    res = RegCreateKeyA(source, "Media", &media);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Media key exists */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = 0xdeadbeef;
    lstrcpyA(prompt, "bbb");
    promptsz = 0xdeadbeef;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", promptsz);

    res = RegSetValueExA(media, "1", 0, REG_SZ, (LPBYTE)"label;prompt", 13);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* disk exists */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    res = RegSetValueExA(media, "2", 0, REG_SZ, (LPBYTE)"one;two", 8);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* now disk 2 exists, get the sizes */
    id = 0;
    labelsz = MAX_PATH;
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 1, &id, NULL, &labelsz,
                                      NULL, &promptsz);
    ok(r == ERROR_SUCCESS || r == ERROR_INVALID_PARAMETER,
      "Expected ERROR_SUCCESS or ERROR_INVALID_PARAMETER, got %d\n", r);
    if (r == ERROR_SUCCESS)
    {
        ok(id == 2, "Expected 2, got %d\n", id);
        ok(labelsz == 3, "Expected 3, got %d\n", labelsz);
        ok(promptsz == 3, "Expected 3, got %d\n", promptsz);
    }

    /* now fill in the values */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 1, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS || r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_SUCCESS or ERROR_INVALID_PARAMETER, got %d\n", r);
    if (r == ERROR_SUCCESS)
    {
        ok(id == 2, "Expected 2, got %d\n", id);
        ok(!lstrcmpA(label, "one"), "Expected \"one\", got \"%s\"\n", label);
        ok(labelsz == 3, "Expected 3, got %d\n", labelsz);
        ok(!lstrcmpA(prompt, "two"), "Expected \"two\", got \"%s\"\n", prompt);
        ok(promptsz == 3, "Expected 3, got %d\n", promptsz);
    }
    else if (r == ERROR_INVALID_PARAMETER)
    {
        ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
        ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
        ok(labelsz == MAX_PATH, "Expected MAX_PATH, got %d\n", labelsz);
        ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
        ok(promptsz == MAX_PATH, "Expected MAX_PATH, got %d\n", promptsz);
    }

    res = RegSetValueExA(media, "4", 0, REG_SZ, (LPBYTE)"three;four", 11);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* disks 1, 2, 4 exist, reset the enumeration */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    /* disks 1, 2, 4 exist, index 1 */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 1, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 2, "Expected 2, got %d\n", id);
    ok(!lstrcmpA(label, "one"), "Expected \"one\", got \"%s\"\n", label);
    ok(labelsz == 3, "Expected 3, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "two"), "Expected \"two\", got \"%s\"\n", prompt);
    ok(promptsz == 3, "Expected 3, got %d\n", promptsz);

    /* disks 1, 2, 4 exist, index 2 */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 2, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 4, "Expected 4, got %d\n", id);
    ok(!lstrcmpA(label, "three"), "Expected \"three\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "four"), "Expected \"four\", got \"%s\"\n", prompt);
    ok(promptsz == 4, "Expected 4, got %d\n", promptsz);

    /* disks 1, 2, 4 exist, index 3, invalid */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 3, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == MAX_PATH, "Expected MAX_PATH, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == MAX_PATH, "Expected MAX_PATH, got %d\n", promptsz);

    /* disks 1, 2, 4 exist, reset the enumeration */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    /* try index 0 again */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    /* jump to index 2 */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 2, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == MAX_PATH, "Expected MAX_PATH, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == MAX_PATH, "Expected MAX_PATH, got %d\n", promptsz);

    /* after error, try index 1 */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 1, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 2, "Expected 2, got %d\n", id);
    ok(!lstrcmpA(label, "one"), "Expected \"one\", got \"%s\"\n", label);
    ok(labelsz == 3, "Expected 3, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "two"), "Expected \"two\", got \"%s\"\n", prompt);
    ok(promptsz == 3, "Expected 3, got %d\n", promptsz);

    /* try index 1 again */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 1, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == MAX_PATH, "Expected MAX_PATH, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == MAX_PATH, "Expected MAX_PATH, got %d\n", promptsz);

    /* NULL pdwDiskId */
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, NULL, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    /* szVolumeLabel is NULL */
    id = 0;
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, NULL, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS || r == ERROR_INVALID_PARAMETER,
      "Expected ERROR_SUCCESS or ERROR_INVALID_PARAMETER, got %d\n", r);
    if (r == ERROR_SUCCESS)
    {
        ok(id == 1, "Expected 1, got %d\n", id);
        ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
        ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
        ok(promptsz == 6, "Expected 6, got %d\n", promptsz);
    }

    /* szVolumeLabel and pcchVolumeLabel are NULL */
    id = 0;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, NULL, NULL,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    /* szVolumeLabel is non-NULL while pcchVolumeLabel is NULL */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, NULL,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS || r == ERROR_INVALID_PARAMETER,
      "Expected ERROR_SUCCESS or ERROR_INVALID_PARAMETER, got %d\n", r);
    if (r == ERROR_SUCCESS)
    {
        ok(id == 1, "Expected 1, got %d\n", id);
        ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
        ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
        ok(promptsz == 6, "Expected 6, got %d\n", promptsz);
    }

    /* szDiskPrompt is NULL */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      NULL, &promptsz);
    ok(r == ERROR_SUCCESS || r == ERROR_INVALID_PARAMETER, "Expected ERROR_SUCCESS, got %d\n", r);
    if (r == ERROR_SUCCESS)
    {
        ok(id == 1, "Expected 1, got %d\n", id);
        ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
        ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
        ok(promptsz == 6, "Expected 6, got %d\n", promptsz);
    }

    /* szDiskPrompt and pcchDiskPrompt are NULL */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);

    /* szDiskPrompt is non-NULL while pcchDiskPrompt is NULL */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, NULL);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == MAX_PATH, "Expected MAX_PATH, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);

    /* pcchVolumeLabel, szDiskPrompt and pcchDiskPrompt are NULL */
    id = 0;
    lstrcpyA(label, "aaa");
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, NULL,
                                      NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(id == 1, "Expected 1, got %d\n", id);

    /* szVolumeLabel, pcchVolumeLabel, szDiskPrompt and pcchDiskPrompt are NULL */
    id = 0;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, NULL, NULL,
                                      NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);

    /* pcchVolumeLabel is exactly 5 */
    lstrcpyA(label, "aaa");
    labelsz = 5;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, NULL, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    /* pcchDiskPrompt is exactly 6 */
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = 6;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, NULL, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    res = RegSetValueExA(media, "1", 0, REG_SZ, (LPBYTE)"label", 13);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* no semicolon */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "label"), "Expected \"label\", got \"%s\"\n", prompt);
    ok(promptsz == 5, "Expected 5, got %d\n", promptsz);

    res = RegSetValueExA(media, "1", 0, REG_SZ, (LPBYTE)"label;", 13);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* semicolon, no disk prompt */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, ""), "Expected \"\", got \"%s\"\n", prompt);
    ok(promptsz == 0, "Expected 0, got %d\n", promptsz);

    res = RegSetValueExA(media, "1", 0, REG_SZ, (LPBYTE)";prompt", 13);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* semicolon, label doesn't exist */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(label, ""), "Expected \"\", got \"%s\"\n", label);
    ok(labelsz == 0, "Expected 0, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    res = RegSetValueExA(media, "1", 0, REG_SZ, (LPBYTE)";", 13);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* semicolon, neither label nor disk prompt exist */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(label, ""), "Expected \"\", got \"%s\"\n", label);
    ok(labelsz == 0, "Expected 0, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, ""), "Expected \"\", got \"%s\"\n", prompt);
    ok(promptsz == 0, "Expected 0, got %d\n", promptsz);

    val = 42;
    res = RegSetValueExA(media, "1", 0, REG_DWORD, (LPBYTE)&val, sizeof(DWORD));
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* type is REG_DWORD */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERUNMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 1, "Expected 1, got %d\n", id);
    ok(!lstrcmpA(label, "#42"), "Expected \"#42\", got \"%s\"\n", label);
    ok(labelsz == 3, "Expected 3, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "#42"), "Expected \"#42\", got \"%s\"\n", prompt);
    ok(promptsz == 3, "Expected 3, got %d\n", promptsz);

    RegDeleteValueA(media, "1");
    RegDeleteValueA(media, "2");
    RegDeleteValueA(media, "4");
    RegDeleteKeyA(media, "");
    RegCloseKey(media);
    RegDeleteKeyA(source, "");
    RegCloseKey(source);
    RegDeleteKeyA(userkey, "");
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_USERMANAGED */

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\Managed\\");
    lstrcatA(keypath, usersid);
    lstrcatA(keypath, "\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &userkey, NULL);
    if (res != ERROR_SUCCESS)
    {
        skip("Product key creation failed with error code %u\n", res);
        goto machine_tests;
    }

    /* user product key exists */
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyExA(userkey, "SourceList", 0, NULL, 0, access, NULL, &source, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = 0xdeadbeef;
    lstrcpyA(prompt, "bbb");
    promptsz = 0xdeadbeef;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", promptsz);

    res = RegCreateKeyExA(source, "Media", 0, NULL, 0, access, NULL, &media, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Media key exists */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = 0xdeadbeef;
    lstrcpyA(prompt, "bbb");
    promptsz = 0xdeadbeef;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", promptsz);

    res = RegSetValueExA(media, "2", 0, REG_SZ, (LPBYTE)"label;prompt", 13);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* disk exists, but no id 1 */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_USERMANAGED,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 2, "Expected 2, got %d\n", id);
    ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    RegDeleteValueA(media, "2");
    delete_key(media, "", access);
    RegCloseKey(media);
    delete_key(source, "", access);
    RegCloseKey(source);
    delete_key(userkey, "", access);
    RegCloseKey(userkey);

    /* MSIINSTALLCONTEXT_MACHINE */

machine_tests:
    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    if (res != ERROR_SUCCESS)
    {
        skip("Product key creation failed with error code %u\n", res);
        LocalFree(usersid);
        return;
    }

    /* machine product key exists */
    r = pMsiSourceListEnumMediaDisksA(prodcode, NULL, MSIINSTALLCONTEXT_MACHINE,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_BAD_CONFIGURATION,
       "Expected ERROR_BAD_CONFIGURATION, got %d\n", r);

    res = RegCreateKeyExA(prodkey, "SourceList", 0, NULL, 0, access, NULL, &source, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* SourceList key exists */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = 0xdeadbeef;
    lstrcpyA(prompt, "bbb");
    promptsz = 0xdeadbeef;
    r = pMsiSourceListEnumMediaDisksA(prodcode, NULL, MSIINSTALLCONTEXT_MACHINE,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", promptsz);

    res = RegCreateKeyExA(source, "Media", 0, NULL, 0, access, NULL, &media, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* Media key exists */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = 0xdeadbeef;
    lstrcpyA(prompt, "bbb");
    promptsz = 0xdeadbeef;
    r = pMsiSourceListEnumMediaDisksA(prodcode, NULL, MSIINSTALLCONTEXT_MACHINE,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_NO_MORE_ITEMS,
       "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", promptsz);

    res = RegSetValueExA(media, "2", 0, REG_SZ, (LPBYTE)"label;prompt", 13);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    /* disk exists, but no id 1 */
    id = 0;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, NULL, MSIINSTALLCONTEXT_MACHINE,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(id == 2, "Expected 2, got %d\n", id);
    ok(!lstrcmpA(label, "label"), "Expected \"label\", got \"%s\"\n", label);
    ok(labelsz == 5, "Expected 5, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "prompt"), "Expected \"prompt\", got \"%s\"\n", prompt);
    ok(promptsz == 6, "Expected 6, got %d\n", promptsz);

    /* szUserSid is non-NULL */
    id = 0xbeef;
    lstrcpyA(label, "aaa");
    labelsz = MAX_PATH;
    lstrcpyA(prompt, "bbb");
    promptsz = MAX_PATH;
    r = pMsiSourceListEnumMediaDisksA(prodcode, usersid, MSIINSTALLCONTEXT_MACHINE,
                                      MSICODE_PRODUCT, 0, &id, label, &labelsz,
                                      prompt, &promptsz);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(id == 0xbeef, "Expected 0xbeef, got %d\n", id);
    ok(!lstrcmpA(label, "aaa"), "Expected \"aaa\", got \"%s\"\n", label);
    ok(labelsz == MAX_PATH, "Expected MAX_PATH, got %d\n", labelsz);
    ok(!lstrcmpA(prompt, "bbb"), "Expected \"bbb\", got \"%s\"\n", prompt);
    ok(promptsz == MAX_PATH, "Expected MAX_PATH, got %d\n", promptsz);

    RegDeleteValueA(media, "2");
    delete_key(media, "", access);
    RegCloseKey(media);
    delete_key(source, "", access);
    RegCloseKey(source);
    delete_key(prodkey, "", access);
    RegCloseKey(prodkey);
    LocalFree(usersid);
}