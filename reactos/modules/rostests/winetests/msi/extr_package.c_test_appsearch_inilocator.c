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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  scalar_t__* LPSTR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_INSTALL_PACKAGE_REJECTED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  INSTALLUILEVEL_NONE ; 
 int /*<<< orphan*/  MAKELONG (int,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiDoActionA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MsiGetPropertyA (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  MsiSetInternalUI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WritePrivateProfileStringA (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  add_appsearch_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_inilocator_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_signature_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_appsearch_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_file_with_version (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_inilocator_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  create_signature_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_test_file (char*) ; 
 int /*<<< orphan*/  delete_win_ini (char*) ; 
 scalar_t__ is_root (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 char* msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__* strrchr (char*,char) ; 

__attribute__((used)) static void test_appsearch_inilocator(void)
{
    MSIHANDLE hpkg, hdb;
    char path[MAX_PATH], expected[MAX_PATH], prop[MAX_PATH];
    BOOL version;
    LPSTR ptr;
    DWORD size;
    UINT r;

    version = TRUE;
    if (!create_file_with_version("test.dll", MAKELONG(2, 1), MAKELONG(4, 3)))
        version = FALSE;

    DeleteFileA("test.dll");

    WritePrivateProfileStringA("Section", "Key", "keydata,field2", "IniFile.ini");

    strcpy(expected, CURR_DIR);
    if (is_root(CURR_DIR)) expected[2] = 0;

    create_test_file("FileName1");
    sprintf(path, "%s\\FileName1", expected);
    WritePrivateProfileStringA("Section", "Key2", path, "IniFile.ini");

    WritePrivateProfileStringA("Section", "Key3", expected, "IniFile.ini");

    sprintf(path, "%s\\IDontExist", expected);
    WritePrivateProfileStringA("Section", "Key4", path, "IniFile.ini");

    create_file_with_version("FileName2.dll", MAKELONG(2, 1), MAKELONG(4, 3));
    sprintf(path, "%s\\FileName2.dll", expected);
    WritePrivateProfileStringA("Section", "Key5", path, "IniFile.ini");

    create_file_with_version("FileName3.dll", MAKELONG(1, 2), MAKELONG(3, 4));
    sprintf(path, "%s\\FileName3.dll", expected);
    WritePrivateProfileStringA("Section", "Key6", path, "IniFile.ini");

    create_file_with_version("FileName4.dll", MAKELONG(2, 1), MAKELONG(4, 3));
    sprintf(path, "%s\\FileName4.dll", expected);
    WritePrivateProfileStringA("Section", "Key7", path, "IniFile.ini");

    hdb = create_package_db();
    ok(hdb, "Expected a valid database handle\n");

    create_appsearch_table(hdb);
    add_appsearch_entry(hdb, "'SIGPROP1', 'NewSignature1'");
    add_appsearch_entry(hdb, "'SIGPROP2', 'NewSignature2'");
    add_appsearch_entry(hdb, "'SIGPROP3', 'NewSignature3'");
    add_appsearch_entry(hdb, "'SIGPROP4', 'NewSignature4'");
    add_appsearch_entry(hdb, "'SIGPROP5', 'NewSignature5'");
    add_appsearch_entry(hdb, "'SIGPROP6', 'NewSignature6'");
    add_appsearch_entry(hdb, "'SIGPROP7', 'NewSignature7'");
    add_appsearch_entry(hdb, "'SIGPROP8', 'NewSignature8'");
    add_appsearch_entry(hdb, "'SIGPROP9', 'NewSignature9'");
    add_appsearch_entry(hdb, "'SIGPROP10', 'NewSignature10'");
    add_appsearch_entry(hdb, "'SIGPROP11', 'NewSignature11'");
    add_appsearch_entry(hdb, "'SIGPROP12', 'NewSignature12'");

    create_inilocator_table(hdb);

    /* msidbLocatorTypeRawValue, field 1 */
    add_inilocator_entry(hdb, "'NewSignature1', 'IniFile.ini', 'Section', 'Key', 1, 2");

    /* msidbLocatorTypeRawValue, field 2 */
    add_inilocator_entry(hdb, "'NewSignature2', 'IniFile.ini', 'Section', 'Key', 2, 2");

    /* msidbLocatorTypeRawValue, entire field */
    add_inilocator_entry(hdb, "'NewSignature3', 'IniFile.ini', 'Section', 'Key', 0, 2");

    /* msidbLocatorTypeFile */
    add_inilocator_entry(hdb, "'NewSignature4', 'IniFile.ini', 'Section', 'Key2', 1, 1");

    /* msidbLocatorTypeDirectory, file */
    add_inilocator_entry(hdb, "'NewSignature5', 'IniFile.ini', 'Section', 'Key2', 1, 0");

    /* msidbLocatorTypeDirectory, directory */
    add_inilocator_entry(hdb, "'NewSignature6', 'IniFile.ini', 'Section', 'Key3', 1, 0");

    /* msidbLocatorTypeFile, file, no signature */
    add_inilocator_entry(hdb, "'NewSignature7', 'IniFile.ini', 'Section', 'Key2', 1, 1");

    /* msidbLocatorTypeFile, dir, no signature */
    add_inilocator_entry(hdb, "'NewSignature8', 'IniFile.ini', 'Section', 'Key3', 1, 1");

    /* msidbLocatorTypeFile, file does not exist */
    add_inilocator_entry(hdb, "'NewSignature9', 'IniFile.ini', 'Section', 'Key4', 1, 1");

    /* msidbLocatorTypeFile, signature with version */
    add_inilocator_entry(hdb, "'NewSignature10', 'IniFile.ini', 'Section', 'Key5', 1, 1");

    /* msidbLocatorTypeFile, signature with version, ver > max */
    add_inilocator_entry(hdb, "'NewSignature11', 'IniFile.ini', 'Section', 'Key6', 1, 1");

    /* msidbLocatorTypeFile, signature with version, sig->name ignored */
    add_inilocator_entry(hdb, "'NewSignature12', 'IniFile.ini', 'Section', 'Key7', 1, 1");

    create_signature_table(hdb);
    add_signature_entry(hdb, "'NewSignature4', 'FileName1', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature9', 'IDontExist', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature10', 'FileName2.dll', '1.1.1.1', '2.1.1.1', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature11', 'FileName3.dll', '1.1.1.1', '2.1.1.1', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature12', 'ignored', '1.1.1.1', '2.1.1.1', '', '', '', '', ''");

    r = package_from_db(hdb, &hpkg);
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        goto error;
    }
    ok(r == ERROR_SUCCESS, "Expected a valid package handle %u\n", r);

    MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);

    r = MsiDoActionA(hpkg, "AppSearch");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "SIGPROP1", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, "keydata"), "Expected \"keydata\", got \"%s\"\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "SIGPROP2", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, "field2"), "Expected \"field2\", got \"%s\"\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "SIGPROP3", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, "keydata,field2"),
       "Expected \"keydata,field2\", got \"%s\"\n", prop);

    size = MAX_PATH;
    sprintf(path, "%s\\FileName1", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP4", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "SIGPROP5", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected \"\", got \"%s\"\n", prop);

    size = MAX_PATH;
    sprintf(path, "%s\\", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP6", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    sprintf(path, "%s\\", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP7", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    if (!is_root(CURR_DIR))
    {
        size = MAX_PATH;
        lstrcpyA(path, expected);
        ptr = strrchr(path, '\\');
        *(ptr + 1) = 0;
        r = MsiGetPropertyA(hpkg, "SIGPROP8", prop, &size);
        ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
        ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);
    }
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "SIGPROP9", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected \"\", got \"%s\"\n", prop);

    if (version)
    {
        size = MAX_PATH;
        sprintf(path, "%s\\FileName2.dll", expected);
        r = MsiGetPropertyA(hpkg, "SIGPROP10", prop, &size);
        ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
        ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

        size = MAX_PATH;
        r = MsiGetPropertyA(hpkg, "SIGPROP11", prop, &size);
        ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
        ok(!lstrcmpA(prop, ""), "Expected \"\", got \"%s\"\n", prop);

        size = MAX_PATH;
        sprintf(path, "%s\\FileName4.dll", expected);
        r = MsiGetPropertyA(hpkg, "SIGPROP12", prop, &size);
        ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
        ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);
    }

    MsiCloseHandle(hpkg);

error:
    delete_win_ini("IniFile.ini");
    DeleteFileA("FileName1");
    DeleteFileA("FileName2.dll");
    DeleteFileA("FileName3.dll");
    DeleteFileA("FileName4.dll");
    DeleteFileA(msifile);
}