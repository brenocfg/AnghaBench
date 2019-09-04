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
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_INSTALL_PACKAGE_REJECTED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INSTALLUILEVEL_NONE ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKELONG (int,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_MACHINE ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERMANAGED ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERUNMANAGED ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiDoActionA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MsiGetPropertyA (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  MsiSetInternalUI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsiSetPropertyA (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_appsearch_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_complocator_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_signature_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_appsearch_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_complocator_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_file_with_version (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  create_signature_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_test_file (char*) ; 
 int /*<<< orphan*/  delete_component_path (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_user_sid () ; 
 scalar_t__ is_process_limited () ; 
 scalar_t__ is_root (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 char* msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_component_path (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_appsearch_complocator(void)
{
    MSIHANDLE hpkg, hdb;
    char path[MAX_PATH], expected[MAX_PATH], prop[MAX_PATH];
    LPSTR usersid;
    DWORD size;
    UINT r;

    if (!(usersid = get_user_sid()))
        return;

    if (is_process_limited())
    {
        skip("process is limited\n");
        return;
    }

    create_test_file("FileName1");
    create_test_file("FileName4");
    set_component_path("FileName1", MSIINSTALLCONTEXT_MACHINE,
                       "{A8AE6692-96BA-4198-8399-145D7D1D0D0E}", NULL, FALSE);

    create_test_file("FileName2");
    set_component_path("FileName2", MSIINSTALLCONTEXT_USERUNMANAGED,
                       "{1D2CE6F3-E81C-4949-AB81-78D7DAD2AF2E}", usersid, FALSE);

    create_test_file("FileName3");
    set_component_path("FileName3", MSIINSTALLCONTEXT_USERMANAGED,
                       "{19E0B999-85F5-4973-A61B-DBE4D66ECB1D}", usersid, FALSE);

    create_test_file("FileName5");
    set_component_path("FileName5", MSIINSTALLCONTEXT_MACHINE,
                       "{F0CCA976-27A3-4808-9DDD-1A6FD50A0D5A}", NULL, TRUE);

    create_test_file("FileName6");
    set_component_path("FileName6", MSIINSTALLCONTEXT_MACHINE,
                       "{C0ECD96F-7898-4410-9667-194BD8C1B648}", NULL, TRUE);

    create_test_file("FileName7");
    set_component_path("FileName7", MSIINSTALLCONTEXT_MACHINE,
                       "{DB20F535-9C26-4127-9C2B-CC45A8B51DA1}", NULL, FALSE);

    /* dir is FALSE, but we're pretending it's a directory */
    set_component_path("IDontExist\\", MSIINSTALLCONTEXT_MACHINE,
                       "{91B7359B-07F2-4221-AA8D-DE102BB87A5F}", NULL, FALSE);

    create_file_with_version("FileName8.dll", MAKELONG(2, 1), MAKELONG(4, 3));
    set_component_path("FileName8.dll", MSIINSTALLCONTEXT_MACHINE,
                       "{4A2E1B5B-4034-4177-833B-8CC35F1B3EF1}", NULL, FALSE);

    create_file_with_version("FileName9.dll", MAKELONG(1, 2), MAKELONG(3, 4));
    set_component_path("FileName9.dll", MSIINSTALLCONTEXT_MACHINE,
                       "{A204DF48-7346-4635-BA2E-66247DBAC9DF}", NULL, FALSE);

    create_file_with_version("FileName10.dll", MAKELONG(2, 1), MAKELONG(4, 3));
    set_component_path("FileName10.dll", MSIINSTALLCONTEXT_MACHINE,
                       "{EC30CE73-4CF9-4908-BABD-1ED82E1515FD}", NULL, FALSE);

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

    create_complocator_table(hdb);

    /* published component, machine, file, signature, misdbLocatorTypeFile */
    add_complocator_entry(hdb, "'NewSignature1', '{A8AE6692-96BA-4198-8399-145D7D1D0D0E}', 1");

    /* published component, user-unmanaged, file, signature, misdbLocatorTypeFile */
    add_complocator_entry(hdb, "'NewSignature2', '{1D2CE6F3-E81C-4949-AB81-78D7DAD2AF2E}', 1");

    /* published component, user-managed, file, signature, misdbLocatorTypeFile */
    add_complocator_entry(hdb, "'NewSignature3', '{19E0B999-85F5-4973-A61B-DBE4D66ECB1D}', 1");

    /* published component, machine, file, signature, misdbLocatorTypeDirectory */
    add_complocator_entry(hdb, "'NewSignature4', '{A8AE6692-96BA-4198-8399-145D7D1D0D0E}', 0");

    /* published component, machine, dir, signature, misdbLocatorTypeDirectory */
    add_complocator_entry(hdb, "'NewSignature5', '{F0CCA976-27A3-4808-9DDD-1A6FD50A0D5A}', 0");

    /* published component, machine, dir, no signature, misdbLocatorTypeDirectory */
    add_complocator_entry(hdb, "'NewSignature6', '{C0ECD96F-7898-4410-9667-194BD8C1B648}', 0");

    /* published component, machine, file, no signature, misdbLocatorTypeFile */
    add_complocator_entry(hdb, "'NewSignature7', '{DB20F535-9C26-4127-9C2B-CC45A8B51DA1}', 1");

    /* unpublished component, no signature, misdbLocatorTypeDir */
    add_complocator_entry(hdb, "'NewSignature8', '{FB671D5B-5083-4048-90E0-481C48D8F3A5}', 0");

    /* published component, no signature, dir does not exist misdbLocatorTypeDir */
    add_complocator_entry(hdb, "'NewSignature9', '{91B7359B-07F2-4221-AA8D-DE102BB87A5F}', 0");

    /* published component, signature w/ ver, misdbLocatorTypeFile */
    add_complocator_entry(hdb, "'NewSignature10', '{4A2E1B5B-4034-4177-833B-8CC35F1B3EF1}', 1");

    /* published component, signature w/ ver, ver > max, misdbLocatorTypeFile */
    add_complocator_entry(hdb, "'NewSignature11', '{A204DF48-7346-4635-BA2E-66247DBAC9DF}', 1");

    /* published component, signature w/ ver, sig->name ignored, misdbLocatorTypeFile */
    add_complocator_entry(hdb, "'NewSignature12', '{EC30CE73-4CF9-4908-BABD-1ED82E1515FD}', 1");

    create_signature_table(hdb);
    add_signature_entry(hdb, "'NewSignature1', 'FileName1', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature2', 'FileName2', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature3', 'FileName3', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature4', 'FileName4', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature5', 'FileName5', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature10', 'FileName8.dll', '1.1.1.1', '2.1.1.1', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature11', 'FileName9.dll', '1.1.1.1', '2.1.1.1', '', '', '', '', ''");
    add_signature_entry(hdb, "'NewSignature12', 'ignored', '1.1.1.1', '2.1.1.1', '', '', '', '', ''");

    r = package_from_db(hdb, &hpkg);
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        goto error;
    }
    ok(r == ERROR_SUCCESS, "Expected a valid package handle %u\n", r);

    r = MsiSetPropertyA(hpkg, "SIGPROP8", "october");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);

    r = MsiDoActionA(hpkg, "AppSearch");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    strcpy(expected, CURR_DIR);
    if (is_root(CURR_DIR)) expected[2] = 0;

    size = MAX_PATH;
    sprintf(path, "%s\\FileName1", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP1", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    sprintf(path, "%s\\FileName2", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP2", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    sprintf(path, "%s\\FileName3", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP3", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    sprintf(path, "%s\\FileName4", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP4", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected \"\", got \"%s\"\n", prop);

    size = MAX_PATH;
    sprintf(path, "%s\\FileName5", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP5", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

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

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "SIGPROP8", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, "october"), "Expected \"october\", got \"%s\"\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "SIGPROP9", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected \"\", got \"%s\"\n", prop);

    size = MAX_PATH;
    sprintf(path, "%s\\FileName8.dll", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP10", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "SIGPROP11", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected \"\", got \"%s\"\n", prop);

    size = MAX_PATH;
    sprintf(path, "%s\\FileName10.dll", expected);
    r = MsiGetPropertyA(hpkg, "SIGPROP12", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, path), "Expected \"%s\", got \"%s\"\n", path, prop);

    delete_component_path("{A8AE6692-96BA-4198-8399-145D7D1D0D0E}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{1D2CE6F3-E81C-4949-AB81-78D7DAD2AF2E}",
                          MSIINSTALLCONTEXT_USERUNMANAGED, usersid);
    delete_component_path("{19E0B999-85F5-4973-A61B-DBE4D66ECB1D}",
                          MSIINSTALLCONTEXT_USERMANAGED, usersid);
    delete_component_path("{F0CCA976-27A3-4808-9DDD-1A6FD50A0D5A}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{C0ECD96F-7898-4410-9667-194BD8C1B648}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{DB20F535-9C26-4127-9C2B-CC45A8B51DA1}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{91B7359B-07F2-4221-AA8D-DE102BB87A5F}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{4A2E1B5B-4034-4177-833B-8CC35F1B3EF1}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{A204DF48-7346-4635-BA2E-66247DBAC9DF}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{EC30CE73-4CF9-4908-BABD-1ED82E1515FD}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);

    MsiCloseHandle(hpkg);

error:
    DeleteFileA("FileName1");
    DeleteFileA("FileName2");
    DeleteFileA("FileName3");
    DeleteFileA("FileName4");
    DeleteFileA("FileName5");
    DeleteFileA("FileName6");
    DeleteFileA("FileName7");
    DeleteFileA("FileName8.dll");
    DeleteFileA("FileName9.dll");
    DeleteFileA("FileName10.dll");
    DeleteFileA(msifile);
    LocalFree(usersid);
}