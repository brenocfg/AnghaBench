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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INSTALL_PACKAGE_REJECTED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ERROR_UNKNOWN_FEATURE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INSTALLSTATE_ABSENT ; 
 int /*<<< orphan*/  INSTALLSTATE_LOCAL ; 
 int /*<<< orphan*/  INSTALLSTATE_SOURCE ; 
 int /*<<< orphan*/  INSTALLSTATE_UNKNOWN ; 
 int /*<<< orphan*/  INSTALLUILEVEL_NONE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDoActionA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MsiSetFeatureStateA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiSetInternalUI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_component_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_directory_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_feature_components_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_feature_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_file_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_component_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_feature_components_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_feature_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_file_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_component_states (int,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_feature_states (int,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_featureparents(void)
{
    MSIHANDLE hpkg;
    UINT r;
    MSIHANDLE hdb;

    hdb = create_package_db();
    ok ( hdb, "failed to create package database\n" );

    add_directory_entry(hdb, "'TARGETDIR', '', 'SourceDir'");

    create_feature_table( hdb );
    create_component_table( hdb );
    create_feature_components_table( hdb );
    create_file_table( hdb );

    /* msidbFeatureAttributesFavorLocal */
    add_feature_entry( hdb, "'zodiac', '', '', '', 2, 1, '', 0" );

    /* msidbFeatureAttributesFavorSource */
    add_feature_entry( hdb, "'perseus', '', '', '', 2, 1, '', 1" );

    /* msidbFeatureAttributesFavorLocal */
    add_feature_entry( hdb, "'orion', '', '', '', 2, 1, '', 0" );

    /* msidbFeatureAttributesUIDisallowAbsent */
    add_feature_entry( hdb, "'lyra', '', '', '', 2, 1, '', 16" );

    /* disabled because of install level */
    add_feature_entry( hdb, "'waters', '', '', '', 15, 101, '', 9" );

    /* child feature of disabled feature */
    add_feature_entry( hdb, "'bayer', 'waters', '', '', 14, 1, '', 9" );

    /* component of disabled feature (install level) */
    add_component_entry( hdb, "'delphinus', '', 'TARGETDIR', 0, '', 'delphinus_file'" );

    /* component of disabled child feature (install level) */
    add_component_entry( hdb, "'hydrus', '', 'TARGETDIR', 0, '', 'hydrus_file'" );

    /* msidbFeatureAttributesFavorLocal:msidbComponentAttributesLocalOnly */
    add_component_entry( hdb, "'leo', '', 'TARGETDIR', 0, '', 'leo_file'" );

    /* msidbFeatureAttributesFavorLocal:msidbComponentAttributesSourceOnly */
    add_component_entry( hdb, "'virgo', '', 'TARGETDIR', 1, '', 'virgo_file'" );

    /* msidbFeatureAttributesFavorLocal:msidbComponentAttributesOptional */
    add_component_entry( hdb, "'libra', '', 'TARGETDIR', 2, '', 'libra_file'" );

    /* msidbFeatureAttributesFavorSource:msidbComponentAttributesLocalOnly */
    add_component_entry( hdb, "'cassiopeia', '', 'TARGETDIR', 0, '', 'cassiopeia_file'" );

    /* msidbFeatureAttributesFavorSource:msidbComponentAttributesSourceOnly */
    add_component_entry( hdb, "'cepheus', '', 'TARGETDIR', 1, '', 'cepheus_file'" );

    /* msidbFeatureAttributesFavorSource:msidbComponentAttributesOptional */
    add_component_entry( hdb, "'andromeda', '', 'TARGETDIR', 2, '', 'andromeda_file'" );

    /* msidbFeatureAttributesFavorLocal:msidbComponentAttributesLocalOnly */
    add_component_entry( hdb, "'canis', '', 'TARGETDIR', 0, '', 'canis_file'" );

    /* msidbFeatureAttributesFavorLocal:msidbComponentAttributesSourceOnly */
    add_component_entry( hdb, "'monoceros', '', 'TARGETDIR', 1, '', 'monoceros_file'" );

    /* msidbFeatureAttributesFavorLocal:msidbComponentAttributesOptional */
    add_component_entry( hdb, "'lepus', '', 'TARGETDIR', 2, '', 'lepus_file'" );

    add_feature_components_entry( hdb, "'zodiac', 'leo'" );
    add_feature_components_entry( hdb, "'zodiac', 'virgo'" );
    add_feature_components_entry( hdb, "'zodiac', 'libra'" );
    add_feature_components_entry( hdb, "'perseus', 'cassiopeia'" );
    add_feature_components_entry( hdb, "'perseus', 'cepheus'" );
    add_feature_components_entry( hdb, "'perseus', 'andromeda'" );
    add_feature_components_entry( hdb, "'orion', 'leo'" );
    add_feature_components_entry( hdb, "'orion', 'virgo'" );
    add_feature_components_entry( hdb, "'orion', 'libra'" );
    add_feature_components_entry( hdb, "'orion', 'cassiopeia'" );
    add_feature_components_entry( hdb, "'orion', 'cepheus'" );
    add_feature_components_entry( hdb, "'orion', 'andromeda'" );
    add_feature_components_entry( hdb, "'orion', 'canis'" );
    add_feature_components_entry( hdb, "'orion', 'monoceros'" );
    add_feature_components_entry( hdb, "'orion', 'lepus'" );
    add_feature_components_entry( hdb, "'waters', 'delphinus'" );
    add_feature_components_entry( hdb, "'bayer', 'hydrus'" );

    add_file_entry( hdb, "'leo_file', 'leo', 'leo.txt', 100, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'virgo_file', 'virgo', 'virgo.txt', 0, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'libra_file', 'libra', 'libra.txt', 0, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'cassiopeia_file', 'cassiopeia', 'cassiopeia.txt', 0, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'cepheus_file', 'cepheus', 'cepheus.txt', 0, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'andromeda_file', 'andromeda', 'andromeda.txt', 0, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'canis_file', 'canis', 'canis.txt', 0, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'monoceros_file', 'monoceros', 'monoceros.txt', 0, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'lepus_file', 'lepus', 'lepus.txt', 0, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'delphinus_file', 'delphinus', 'delphinus.txt', 0, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'hydrus_file', 'hydrus', 'hydrus.txt', 0, '', '1033', 8192, 1" );

    r = package_from_db( hdb, &hpkg );
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok( r == ERROR_SUCCESS, "failed to create package %u\n", r );

    MsiCloseHandle( hdb );

    MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);

    r = MsiDoActionA( hpkg, "CostInitialize");
    ok( r == ERROR_SUCCESS, "cost init failed\n");

    r = MsiDoActionA( hpkg, "FileCost");
    ok( r == ERROR_SUCCESS, "file cost failed\n");

    r = MsiDoActionA( hpkg, "CostFinalize");
    ok( r == ERROR_SUCCESS, "cost finalize failed\n");

    test_feature_states( __LINE__, hpkg, "zodiac", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_LOCAL, FALSE );
    test_feature_states( __LINE__, hpkg, "perseus", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_SOURCE, FALSE );
    test_feature_states( __LINE__, hpkg, "orion", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_LOCAL, FALSE );
    test_feature_states( __LINE__, hpkg, "lyra", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_LOCAL, FALSE );
    test_feature_states( __LINE__, hpkg, "waters", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_UNKNOWN, FALSE );
    test_feature_states( __LINE__, hpkg, "bayer", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_UNKNOWN, FALSE );

    test_component_states( __LINE__, hpkg, "leo", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_LOCAL, FALSE );
    test_component_states( __LINE__, hpkg, "virgo", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_SOURCE, FALSE );
    test_component_states( __LINE__, hpkg, "libra", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_LOCAL, FALSE );
    test_component_states( __LINE__, hpkg, "cassiopeia", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_LOCAL, FALSE );
    test_component_states( __LINE__, hpkg, "cepheus", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_SOURCE, FALSE );
    test_component_states( __LINE__, hpkg, "andromeda", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_LOCAL, FALSE );
    test_component_states( __LINE__, hpkg, "canis", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_LOCAL, FALSE );
    test_component_states( __LINE__, hpkg, "monoceros", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_SOURCE, FALSE );
    test_component_states( __LINE__, hpkg, "lepus", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_LOCAL, FALSE );
    test_component_states( __LINE__, hpkg, "delphinus", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_UNKNOWN, FALSE );
    test_component_states( __LINE__, hpkg, "hydrus", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_UNKNOWN, FALSE );

    r = MsiSetFeatureStateA(hpkg, "orion", INSTALLSTATE_ABSENT);
    ok( r == ERROR_SUCCESS, "failed to set feature state: %d\n", r);

    r = MsiSetFeatureStateA(hpkg, "lyra", INSTALLSTATE_ABSENT);
    ok( r == ERROR_SUCCESS, "failed to set feature state: %d\n", r);

    r = MsiSetFeatureStateA(hpkg, "nosuchfeature", INSTALLSTATE_ABSENT);
    ok( r == ERROR_UNKNOWN_FEATURE, "Expected ERROR_UNKNOWN_FEATURE, got %u\n", r);

    test_feature_states( __LINE__, hpkg, "zodiac", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_LOCAL, FALSE );
    test_feature_states( __LINE__, hpkg, "perseus", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_SOURCE, FALSE );
    test_feature_states( __LINE__, hpkg, "orion", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_ABSENT, FALSE );
    test_feature_states( __LINE__, hpkg, "lyra", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_ABSENT, FALSE );
    test_feature_states( __LINE__, hpkg, "waters", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_UNKNOWN, FALSE );
    test_feature_states( __LINE__, hpkg, "bayer", ERROR_SUCCESS, INSTALLSTATE_ABSENT, INSTALLSTATE_UNKNOWN, FALSE );

    test_component_states( __LINE__, hpkg, "leo", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_LOCAL, FALSE );
    test_component_states( __LINE__, hpkg, "virgo", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_SOURCE, FALSE );
    test_component_states( __LINE__, hpkg, "libra", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_LOCAL, FALSE );
    test_component_states( __LINE__, hpkg, "cassiopeia", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_LOCAL, FALSE );
    test_component_states( __LINE__, hpkg, "cepheus", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_SOURCE, FALSE );
    test_component_states( __LINE__, hpkg, "andromeda", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_SOURCE, FALSE );
    test_component_states( __LINE__, hpkg, "canis", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_UNKNOWN, FALSE );
    test_component_states( __LINE__, hpkg, "monoceros", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_UNKNOWN, FALSE );
    test_component_states( __LINE__, hpkg, "lepus", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_UNKNOWN, FALSE );
    test_component_states( __LINE__, hpkg, "delphinus", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_UNKNOWN, FALSE );
    test_component_states( __LINE__, hpkg, "hydrus", ERROR_SUCCESS, INSTALLSTATE_UNKNOWN, INSTALLSTATE_UNKNOWN, FALSE );

    MsiCloseHandle(hpkg);
    DeleteFileA(msifile);
}