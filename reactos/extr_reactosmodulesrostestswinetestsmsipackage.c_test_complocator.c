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
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 char* ERROR_INSTALL_PACKAGE_REJECTED ; 
 char* ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INSTALLUILEVEL_NONE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_MACHINE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 char* MsiDoActionA (int /*<<< orphan*/ ,char*) ; 
 char* MsiGetPropertyA (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  MsiSetInternalUI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/  add_appsearch_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_complocator_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_signature_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_appsearch_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_complocator_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  create_signature_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_test_file (char*) ; 
 int /*<<< orphan*/  delete_component_path (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_root (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,int /*<<< orphan*/ ) ; 
 char* msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_component_path (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_complocator(void)
{
    MSIHANDLE hdb, hpkg;
    UINT r;
    CHAR prop[MAX_PATH];
    CHAR expected[MAX_PATH];
    DWORD size = MAX_PATH;

    hdb = create_package_db();
    ok(hdb, "failed to create package database\n");

    create_appsearch_table(hdb);
    add_appsearch_entry(hdb, "'ABELISAURUS', 'abelisaurus'");
    add_appsearch_entry(hdb, "'BACTROSAURUS', 'bactrosaurus'");
    add_appsearch_entry(hdb, "'CAMELOTIA', 'camelotia'");
    add_appsearch_entry(hdb, "'DICLONIUS', 'diclonius'");
    add_appsearch_entry(hdb, "'ECHINODON', 'echinodon'");
    add_appsearch_entry(hdb, "'FALCARIUS', 'falcarius'");
    add_appsearch_entry(hdb, "'GALLIMIMUS', 'gallimimus'");
    add_appsearch_entry(hdb, "'HAGRYPHUS', 'hagryphus'");
    add_appsearch_entry(hdb, "'IGUANODON', 'iguanodon'");
    add_appsearch_entry(hdb, "'JOBARIA', 'jobaria'");
    add_appsearch_entry(hdb, "'KAKURU', 'kakuru'");
    add_appsearch_entry(hdb, "'LABOCANIA', 'labocania'");
    add_appsearch_entry(hdb, "'MEGARAPTOR', 'megaraptor'");
    add_appsearch_entry(hdb, "'NEOSODON', 'neosodon'");
    add_appsearch_entry(hdb, "'OLOROTITAN', 'olorotitan'");
    add_appsearch_entry(hdb, "'PANTYDRACO', 'pantydraco'");

    create_complocator_table(hdb);
    add_complocator_entry(hdb, "'abelisaurus', '{E3619EED-305A-418C-B9C7-F7D7377F0934}', 1");
    add_complocator_entry(hdb, "'bactrosaurus', '{D56B688D-542F-42Ef-90FD-B6DA76EE8119}', 0");
    add_complocator_entry(hdb, "'camelotia', '{8211BE36-2466-47E3-AFB7-6AC72E51AED2}', 1");
    add_complocator_entry(hdb, "'diclonius', '{5C767B20-A33C-45A4-B80B-555E512F01AE}', 0");
    add_complocator_entry(hdb, "'echinodon', '{A19E16C5-C75D-4699-8111-C4338C40C3CB}', 1");
    add_complocator_entry(hdb, "'falcarius', '{17762FA1-A7AE-4CC6-8827-62873C35361D}', 0");
    add_complocator_entry(hdb, "'gallimimus', '{75EBF568-C959-41E0-A99E-9050638CF5FB}', 1");
    add_complocator_entry(hdb, "'hagrphus', '{D4969B72-17D9-4AB6-BE49-78F2FEE857AC}', 0");
    add_complocator_entry(hdb, "'iguanodon', '{8E0DA02E-F6A7-4A8F-B25D-6F564C492308}', 1");
    add_complocator_entry(hdb, "'jobaria', '{243C22B1-8C51-4151-B9D1-1AE5265E079E}', 0");
    add_complocator_entry(hdb, "'kakuru', '{5D0F03BA-50BC-44F2-ABB1-72C972F4E514}', 1");
    add_complocator_entry(hdb, "'labocania', '{C7DDB60C-7828-4046-A6F8-699D5E92F1ED}', 0");
    add_complocator_entry(hdb, "'megaraptor', '{8B1034B7-BD5E-41ac-B52C-0105D3DFD74D}', 1");
    add_complocator_entry(hdb, "'neosodon', '{0B499649-197A-48EF-93D2-AF1C17ED6E90}', 0");
    add_complocator_entry(hdb, "'olorotitan', '{54E9E91F-AED2-46D5-A25A-7E50AFA24513}', 1");
    add_complocator_entry(hdb, "'pantydraco', '{2A989951-5565-4FA7-93A7-E800A3E67D71}', 0");

    create_signature_table(hdb);
    add_signature_entry(hdb, "'abelisaurus', 'abelisaurus', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'bactrosaurus', 'bactrosaurus', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'camelotia', 'camelotia', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'diclonius', 'diclonius', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'iguanodon', 'iguanodon', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'jobaria', 'jobaria', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'kakuru', 'kakuru', '', '', '', '', '', '', ''");
    add_signature_entry(hdb, "'labocania', 'labocania', '', '', '', '', '', '', ''");

    r = package_from_db(hdb, &hpkg);
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok(r == ERROR_SUCCESS, "failed to create package %u\n", r);

    MsiCloseHandle(hdb);

    create_test_file("abelisaurus");
    create_test_file("bactrosaurus");
    create_test_file("camelotia");
    create_test_file("diclonius");
    create_test_file("echinodon");
    create_test_file("falcarius");
    create_test_file("gallimimus");
    create_test_file("hagryphus");
    CreateDirectoryA("iguanodon", NULL);
    CreateDirectoryA("jobaria", NULL);
    CreateDirectoryA("kakuru", NULL);
    CreateDirectoryA("labocania", NULL);
    CreateDirectoryA("megaraptor", NULL);
    CreateDirectoryA("neosodon", NULL);
    CreateDirectoryA("olorotitan", NULL);
    CreateDirectoryA("pantydraco", NULL);

    set_component_path("abelisaurus", MSIINSTALLCONTEXT_MACHINE,
                       "{E3619EED-305A-418C-B9C7-F7D7377F0934}", NULL, FALSE);
    set_component_path("bactrosaurus", MSIINSTALLCONTEXT_MACHINE,
                       "{D56B688D-542F-42Ef-90FD-B6DA76EE8119}", NULL, FALSE);
    set_component_path("echinodon", MSIINSTALLCONTEXT_MACHINE,
                       "{A19E16C5-C75D-4699-8111-C4338C40C3CB}", NULL, FALSE);
    set_component_path("falcarius", MSIINSTALLCONTEXT_MACHINE,
                       "{17762FA1-A7AE-4CC6-8827-62873C35361D}", NULL, FALSE);
    set_component_path("iguanodon", MSIINSTALLCONTEXT_MACHINE,
                       "{8E0DA02E-F6A7-4A8F-B25D-6F564C492308}", NULL, FALSE);
    set_component_path("jobaria", MSIINSTALLCONTEXT_MACHINE,
                       "{243C22B1-8C51-4151-B9D1-1AE5265E079E}", NULL, FALSE);
    set_component_path("megaraptor", MSIINSTALLCONTEXT_MACHINE,
                       "{8B1034B7-BD5E-41ac-B52C-0105D3DFD74D}", NULL, FALSE);
    set_component_path("neosodon", MSIINSTALLCONTEXT_MACHINE,
                       "{0B499649-197A-48EF-93D2-AF1C17ED6E90}", NULL, FALSE);

    MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);

    r = MsiDoActionA(hpkg, "AppSearch");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "ABELISAURUS", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    lstrcpyA(expected, CURR_DIR);
    if (!is_root(CURR_DIR)) lstrcatA(expected, "\\");
    lstrcatA(expected, "abelisaurus");
    ok(!lstrcmpA(prop, expected) || !lstrcmpA(prop, ""),
       "Expected %s or empty string, got %s\n", expected, prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "BACTROSAURUS", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "CAMELOTIA", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "DICLONIUS", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "ECHINODON", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    lstrcpyA(expected, CURR_DIR);
    if (!is_root(CURR_DIR)) lstrcatA(expected, "\\");
    ok(!lstrcmpA(prop, expected) || !lstrcmpA(prop, ""),
       "Expected %s or empty string, got %s\n", expected, prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "FALCARIUS", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "GALLIMIMUS", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "HAGRYPHUS", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "IGUANODON", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "JOBARIA", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "KAKURU", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "LABOCANIA", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "MEGARAPTOR", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    lstrcpyA(expected, CURR_DIR);
    if (!is_root(CURR_DIR)) lstrcatA(expected, "\\");
    ok(!lstrcmpA(prop, expected) || !lstrcmpA(prop, ""),
       "Expected %s or empty string, got %s\n", expected, prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "NEOSODON", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    lstrcpyA(expected, CURR_DIR);
    if (!is_root(CURR_DIR)) lstrcatA(expected, "\\");
    lstrcatA(expected, "neosodon\\");
    ok(!lstrcmpA(prop, expected) || !lstrcmpA(prop, ""),
       "Expected %s or empty string, got %s\n", expected, prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "OLOROTITAN", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "PANTYDRACO", prop, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(prop, ""), "Expected , got %s\n", prop);

    MsiCloseHandle(hpkg);
    DeleteFileA("abelisaurus");
    DeleteFileA("bactrosaurus");
    DeleteFileA("camelotia");
    DeleteFileA("diclonius");
    DeleteFileA("echinodon");
    DeleteFileA("falcarius");
    DeleteFileA("gallimimus");
    DeleteFileA("hagryphus");
    RemoveDirectoryA("iguanodon");
    RemoveDirectoryA("jobaria");
    RemoveDirectoryA("kakuru");
    RemoveDirectoryA("labocania");
    RemoveDirectoryA("megaraptor");
    RemoveDirectoryA("neosodon");
    RemoveDirectoryA("olorotitan");
    RemoveDirectoryA("pantydraco");
    delete_component_path("{E3619EED-305A-418C-B9C7-F7D7377F0934}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{D56B688D-542F-42Ef-90FD-B6DA76EE8119}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{A19E16C5-C75D-4699-8111-C4338C40C3CB}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{17762FA1-A7AE-4CC6-8827-62873C35361D}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{8E0DA02E-F6A7-4A8F-B25D-6F564C492308}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{243C22B1-8C51-4151-B9D1-1AE5265E079E}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{8B1034B7-BD5E-41ac-B52C-0105D3DFD74D}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    delete_component_path("{0B499649-197A-48EF-93D2-AF1C17ED6E90}",
                          MSIINSTALLCONTEXT_MACHINE, NULL);
    DeleteFileA(msifile);
}