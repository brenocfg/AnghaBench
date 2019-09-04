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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  int MSIHANDLE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int,char*) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_WOW64_64KEY ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MsiCloseHandle (int) ; 
 scalar_t__ MsiDatabaseCommit (int) ; 
 scalar_t__ MsiGetProductPropertyA (int,char*,char*,int*) ; 
 scalar_t__ MsiGetProductPropertyW (int,char const*,char*,int*) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ MsiOpenProductA (char*,int*) ; 
 scalar_t__ MsiSetPropertyA (int,char*,char*) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ add_property_entry (int,char*) ; 
 int /*<<< orphan*/  create_property_table (int) ; 
 int /*<<< orphan*/  create_test_guid (char*,char*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int lstrlenA (char*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 char* msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ run_query (int,char*) ; 
 scalar_t__ set_summary_info (int) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  squash_guid (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_MsiGetProductProperty(void)
{
    static const WCHAR prodcode_propW[] = {'P','r','o','d','u','c','t','C','o','d','e',0};
    static const WCHAR nonexistentW[] = {'I','D','o','n','t','E','x','i','s','t',0};
    static const WCHAR newpropW[] = {'N','e','w','P','r','o','p','e','r','t','y',0};
    static const WCHAR appleW[] = {'a','p','p','l','e',0};
    static const WCHAR emptyW[] = {0};
    WCHAR valW[MAX_PATH];
    MSIHANDLE hprod, hdb;
    CHAR val[MAX_PATH];
    CHAR path[MAX_PATH];
    CHAR query[MAX_PATH];
    CHAR keypath[MAX_PATH*2];
    CHAR prodcode[MAX_PATH];
    WCHAR prodcodeW[MAX_PATH];
    CHAR prod_squashed[MAX_PATH];
    WCHAR prod_squashedW[MAX_PATH];
    HKEY prodkey, userkey, props;
    DWORD size;
    LONG res;
    UINT r;
    REGSAM access = KEY_ALL_ACCESS;

    GetCurrentDirectoryA(MAX_PATH, path);
    lstrcatA(path, "\\");

    create_test_guid(prodcode, prod_squashed);
    MultiByteToWideChar(CP_ACP, 0, prodcode, -1, prodcodeW, MAX_PATH);
    squash_guid(prodcodeW, prod_squashedW);

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiDatabaseCommit(hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = set_summary_info(hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = run_query(hdb,
            "CREATE TABLE `Directory` ( "
            "`Directory` CHAR(255) NOT NULL, "
            "`Directory_Parent` CHAR(255), "
            "`DefaultDir` CHAR(255) NOT NULL "
            "PRIMARY KEY `Directory`)");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    create_property_table(hdb);

    sprintf(query, "'ProductCode', '%s'", prodcode);
    r = add_property_entry(hdb, query);

    r = MsiDatabaseCommit(hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    MsiCloseHandle(hdb);

    lstrcpyA(keypath, "Software\\Classes\\Installer\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &prodkey, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    lstrcpyA(keypath, "Software\\Microsoft\\Windows\\CurrentVersion\\");
    lstrcatA(keypath, "Installer\\UserData\\S-1-5-18\\Products\\");
    lstrcatA(keypath, prod_squashed);

    res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, access, NULL, &userkey, NULL);
    if (res == ERROR_ACCESS_DENIED)
    {
        skip("Not enough rights to perform tests\n");
        RegDeleteKeyA(prodkey, "");
        RegCloseKey(prodkey);
        return;
    }
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    res = RegCreateKeyExA(userkey, "InstallProperties", 0, NULL, 0, access, NULL, &props, NULL);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    lstrcpyA(val, path);
    lstrcatA(val, "\\");
    lstrcatA(val, msifile);
    res = RegSetValueExA(props, "LocalPackage", 0, REG_SZ,
                         (const BYTE *)val, lstrlenA(val) + 1);
    ok(res == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", res);

    hprod = 0xdeadbeef;
    r = MsiOpenProductA(prodcode, &hprod);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(hprod != 0 && hprod != 0xdeadbeef, "Expected a valid product handle\n");

    /* hProduct is invalid */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(0xdeadbeef, "ProductCode", val, &size);
    ok(r == ERROR_INVALID_HANDLE,
       "Expected ERROR_INVALID_HANDLE, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(0xdeadbeef, prodcode_propW, valW, &size);
    ok(r == ERROR_INVALID_HANDLE,
       "Expected ERROR_INVALID_HANDLE, got %d\n", r);
    ok(!lstrcmpW(valW, appleW),
       "Expected val to be unchanged, got %s\n", wine_dbgstr_w(valW));
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* szProperty is NULL */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(hprod, NULL, val, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    size = MAX_PATH;
    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(hprod, NULL, valW, &size);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpW(valW, appleW),
       "Expected val to be unchanged, got %s\n", wine_dbgstr_w(valW));
    ok(size == MAX_PATH, "Expected size to be unchanged, got %d\n", size);

    /* szProperty is empty */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(hprod, "", val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, ""), "Expected \"\", got \"%s\"\n", val);
    ok(size == 0, "Expected 0, got %d\n", size);

    size = MAX_PATH;
    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(hprod, emptyW, valW, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(*valW == 0, "Expected \"\", got %s\n", wine_dbgstr_w(valW));
    ok(size == 0, "Expected 0, got %d\n", size);

    /* get the property */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(hprod, "ProductCode", val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, val);
    ok(size == lstrlenA(prodcode),
       "Expected %d, got %d\n", lstrlenA(prodcode), size);

    size = MAX_PATH;
    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(hprod, prodcode_propW, valW, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpW(valW, prodcodeW),
       "Expected %s, got %s\n", wine_dbgstr_w(prodcodeW), wine_dbgstr_w(valW));
    ok(size == lstrlenW(prodcodeW),
       "Expected %d, got %d\n", lstrlenW(prodcodeW), size);

    /* lpValueBuf is NULL */
    size = MAX_PATH;
    r = MsiGetProductPropertyA(hprod, "ProductCode", NULL, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(size == lstrlenA(prodcode),
       "Expected %d, got %d\n", lstrlenA(prodcode), size);

    size = MAX_PATH;
    r = MsiGetProductPropertyW(hprod, prodcode_propW, NULL, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(size == lstrlenW(prodcodeW),
       "Expected %d, got %d\n", lstrlenW(prodcodeW), size);

    /* pcchValueBuf is NULL */
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(hprod, "ProductCode", val, NULL);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpA(val, "apple"),
       "Expected val to be unchanged, got \"%s\"\n", val);
    ok(size == lstrlenA(prodcode),
       "Expected %d, got %d\n", lstrlenA(prodcode), size);

    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(hprod, prodcode_propW, valW, NULL);
    ok(r == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", r);
    ok(!lstrcmpW(valW, appleW),
       "Expected val to be unchanged, got %s\n", wine_dbgstr_w(valW));
    ok(size == lstrlenW(prodcodeW),
       "Expected %d, got %d\n", lstrlenW(prodcodeW), size);

    /* pcchValueBuf is too small */
    size = 4;
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(hprod, "ProductCode", val, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!strncmp(val, prodcode, 3),
       "Expected first 3 chars of \"%s\", got \"%s\"\n", prodcode, val);
    ok(size == lstrlenA(prodcode),
       "Expected %d, got %d\n", lstrlenA(prodcode), size);

    size = 4;
    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(hprod, prodcode_propW, valW, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!memcmp(valW, prodcodeW, 3 * sizeof(WCHAR)),
       "Expected first 3 chars of %s, got %s\n", wine_dbgstr_w(prodcodeW), wine_dbgstr_w(valW));
    ok(size == lstrlenW(prodcodeW),
       "Expected %d, got %d\n", lstrlenW(prodcodeW), size);

    /* pcchValueBuf does not leave room for NULL terminator */
    size = lstrlenA(prodcode);
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(hprod, "ProductCode", val, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!strncmp(val, prodcode, lstrlenA(prodcode) - 1),
       "Expected first 37 chars of \"%s\", got \"%s\"\n", prodcode, val);
    ok(size == lstrlenA(prodcode),
       "Expected %d, got %d\n", lstrlenA(prodcode), size);

    size = lstrlenW(prodcodeW);
    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(hprod, prodcode_propW, valW, &size);
    ok(r == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", r);
    ok(!memcmp(valW, prodcodeW, lstrlenW(prodcodeW) - 1),
       "Expected first 37 chars of %s, got %s\n", wine_dbgstr_w(prodcodeW), wine_dbgstr_w(valW));
    ok(size == lstrlenW(prodcodeW),
       "Expected %d, got %d\n", lstrlenW(prodcodeW), size);

    /* pcchValueBuf has enough room for NULL terminator */
    size = lstrlenA(prodcode) + 1;
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(hprod, "ProductCode", val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, val);
    ok(size == lstrlenA(prodcode),
       "Expected %d, got %d\n", lstrlenA(prodcode), size);

    size = lstrlenW(prodcodeW) + 1;
    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(hprod, prodcode_propW, valW, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpW(valW, prodcodeW),
       "Expected %s, got %s\n", wine_dbgstr_w(prodcodeW), wine_dbgstr_w(valW));
    ok(size == lstrlenW(prodcodeW),
       "Expected %d, got %d\n", lstrlenW(prodcodeW), size);

    /* nonexistent property */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(hprod, "IDontExist", val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, ""), "Expected \"\", got \"%s\"\n", val);
    ok(size == 0, "Expected 0, got %d\n", size);

    size = MAX_PATH;
    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(hprod, nonexistentW, valW, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpW(valW, emptyW), "Expected \"\", got %s\n", wine_dbgstr_w(valW));
    ok(size == 0, "Expected 0, got %d\n", size);

    r = MsiSetPropertyA(hprod, "NewProperty", "value");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* non-product property set */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(hprod, "NewProperty", val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, ""), "Expected \"\", got \"%s\"\n", val);
    ok(size == 0, "Expected 0, got %d\n", size);

    size = MAX_PATH;
    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(hprod, newpropW, valW, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpW(valW, emptyW), "Expected \"\", got %s\n", wine_dbgstr_w(valW));
    ok(size == 0, "Expected 0, got %d\n", size);

    r = MsiSetPropertyA(hprod, "ProductCode", "value");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    /* non-product property that is also a product property set */
    size = MAX_PATH;
    lstrcpyA(val, "apple");
    r = MsiGetProductPropertyA(hprod, "ProductCode", val, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(val, prodcode),
       "Expected \"%s\", got \"%s\"\n", prodcode, val);
    ok(size == lstrlenA(prodcode),
       "Expected %d, got %d\n", lstrlenA(prodcode), size);

    size = MAX_PATH;
    lstrcpyW(valW, appleW);
    r = MsiGetProductPropertyW(hprod, prodcode_propW, valW, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpW(valW, prodcodeW),
       "Expected %s, got %s\n", wine_dbgstr_w(prodcodeW), wine_dbgstr_w(valW));
    ok(size == lstrlenW(prodcodeW),
       "Expected %d, got %d\n", lstrlenW(prodcodeW), size);

    MsiCloseHandle(hprod);

    RegDeleteValueA(props, "LocalPackage");
    delete_key(props, "", access);
    RegCloseKey(props);
    delete_key(userkey, "", access);
    RegCloseKey(userkey);
    delete_key(prodkey, "", access);
    RegCloseKey(prodkey);
    DeleteFileA(msifile);
}