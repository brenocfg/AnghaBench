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
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 char* CURR_DIR ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 char* ERROR_INSTALL_PACKAGE_REJECTED ; 
 char* ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  INSTALLUILEVEL_NONE ; 
 int /*<<< orphan*/  MAKELONG (int,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 char* MsiDoActionA (int /*<<< orphan*/ ,char*) ; 
 char* MsiGetPropertyA (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  MsiSetInternalUI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  add_appsearch_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_drlocator_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_reglocator_entry (int /*<<< orphan*/ ,char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  add_signature_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_appsearch_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_drlocator_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_file_with_version (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  create_reglocator_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_signature_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_test_file (char*) ; 
 scalar_t__ is_root (char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 char* msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  search_absolute_directory (char*,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_appsearch_drlocator(void)
{
    MSIHANDLE hpkg, hdb;
    char path[MAX_PATH], expected[MAX_PATH], prop[MAX_PATH];
    BOOL version;
    DWORD size;
    UINT r;

    version = TRUE;
    if (!create_file_with_version("test.dll", MAKELONG(2, 1), MAKELONG(4, 3)))
        version = FALSE;

    DeleteFileA("test.dll");

    create_test_file("FileName1");
    CreateDirectoryA("one", NULL);
    CreateDirectoryA("one\\two", NULL);
    CreateDirectoryA("one\\two\\three", NULL);
    create_test_file("one\\two\\three\\FileName2");
    CreateDirectoryA("another", NULL);
    create_file_with_version("FileName3.dll", MAKELONG(2, 1), MAKELONG(4, 3));
    create_file_with_version("FileName4.dll", MAKELONG(1, 2), MAKELONG(3, 4));
    create_file_with_version("FileName5.dll", MAKELONG(2, 1), MAKELONG(4, 3));

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
    add_appsearch_entry(hdb, "'SIGPROP13', 'NewSignature13'");

    create_drlocator_table(hdb);

    strcpy(expected, CURR_DIR);
    if (is_root(CURR_DIR)) expected[2] = 0;

    /* no parent, full path, depth 0, signature */
    sprintf(path, "'NewSignature1', '', '%s', 0", expected);
    add_drlocator_entry(hdb, path);

    /* no parent, full path, depth 0, no signature */
    sprintf(path, "'NewSignature2', '', '%s', 0", expected);
    add_drlocator_entry(hdb, path);

    /* no parent, relative path, depth 0, no signature */
    sprintf(path, "'NewSignature3', '', '%s', 0", expected + 3);
    add_drlocator_entry(hdb, path);

    /* no parent, full path, depth 2, signature */
    sprintf(path, "'NewSignature4', '', '%s', 2", expected);
    add_drlocator_entry(hdb, path);

    /* no parent, full path, depth 3, signature */
    sprintf(path, "'NewSignature5', '', '%s', 3", expected);
    add_drlocator_entry(hdb, path);

    /* no parent, full path, depth 1, signature is dir */
    sprintf(path, "'NewSignature6', '', '%s', 1", expected);
    add_drlocator_entry(hdb, path);

    /* parent is in DrLocator, relative path, depth 0, signature */
    sprintf(path, "'NewSignature7', 'NewSignature1', 'one\\two\\three', 1");
    add_drlocator_entry(hdb, path);

    /* no parent, full path, depth 0, signature w/ version */
    sprintf(path, "'NewSignature8', '', '%s', 0", expected);
    add_drlocator_entry(hdb, path);

    /* no parent, full path, depth 0, signature w/ version, ver > max */
    sprintf(path, "'NewSignature9', '', '%s', 0", expected);
    add_drlocator_entry(hdb, path);

    /* no parent, full path, depth 0, signature w/ version, sig->name not ignored */
    sprintf(path, "'NewSignature10', '', '%s', 0", expected);
    add_drlocator_entry(hdb, path);

    /* no parent, relative empty path, depth 0, no signature */
    sprintf(path, "'NewSignature11', '', '', 0");
    add_drlocator_entry(hdb, path);

    create_reglocator_table(hdb);

    /* parent */
    add_reglocator_entry(hdb, "NewSignature12", 2, "htmlfile\\shell\\open\\nonexistent", "", 1);

    /* parent is in RegLocator, no path, depth 0, no signature */
    sprintf(path, "'NewSignature13', 'NewSignature12', '', 0");
    add_drlocator_entry(hdb, path);

    create_signature_table(hdb);
    add_signature_entry(hdb, "'NewSignature1', 'FileName1', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature4', 'FileName2', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature5', 'FileName2', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature6', 'another', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature7', 'FileName2', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature8', 'FileName3.dll', '1.1.1.1', '2.1.1.1', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature9', 'FileName4.dll', '1.1.1.1', '2.1.1.1', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature10', 'necessary', '1.1.1.1', '2.1.1.1', '', '', '', '', ''");

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
    sprintf(path, "%s\\FileName1", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP1", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    sprintf(path, "%s\\", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP2", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    search_absolute_directory(path, expected + 3);
    r = MsiGetPropertyA(hpkg, "SIGPROP3", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpiA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "SIGPROP4", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected \"\", got \"%s\"\n", prop);

    size = MAX_PATH;
    sprintf(path, "%s\\one\\two\\three\\FileName2", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP5", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "SIGPROP6", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected \"\", got \"%s\"\n", prop);

    size = MAX_PATH;
    sprintf(path, "%s\\one\\two\\three\\FileName2", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP7", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    if (version)
    {
        size = MAX_PATH;
        sprintf(path, "%s\\FileName3.dll", expected);
        r = MsiGetPropertyA(hpkg, "SIGPROP8", prop, &size);
        ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
        ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

        size = MAX_PATH;
        r = MsiGetPropertyA(hpkg, "SIGPROP9", prop, &size);
        ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
        ok(!lstrcmpA(prop, ""), "Expected \"\", got \"%s\"\n", prop);

        size = MAX_PATH;
        r = MsiGetPropertyA(hpkg, "SIGPROP10", prop, &size);
        ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
        ok(!lstrcmpA(prop, ""), "Expected \"\", got \"%s\"\n", prop);
    }

    size = MAX_PATH;
    search_absolute_directory(path, "");
    r = MsiGetPropertyA(hpkg, "SIGPROP11", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpiA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    strcpy(path, "c:\\");
    r = MsiGetPropertyA(hpkg, "SIGPROP13", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!prop[0], "Expected \"\", got \"%s\"\n", prop);

    MsiCloseHandle(hpkg);

error:
    DeleteFileA("FileName1");
    DeleteFileA("FileName3.dll");
    DeleteFileA("FileName4.dll");
    DeleteFileA("FileName5.dll");
    DeleteFileA("one\\two\\three\\FileName2");
    RemoveDirectoryA("one\\two\\three");
    RemoveDirectoryA("one\\two");
    RemoveDirectoryA("one");
    RemoveDirectoryA("another");
    DeleteFileA(msifile);
}