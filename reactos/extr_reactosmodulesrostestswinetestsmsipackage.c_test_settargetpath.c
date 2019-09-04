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
typedef  int /*<<< orphan*/  buffer ;
typedef  char* UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 char* ERROR_DIRECTORY ; 
 char* ERROR_INSTALL_PACKAGE_REJECTED ; 
 char* ERROR_INVALID_HANDLE ; 
 char* ERROR_INVALID_PARAMETER ; 
 char* ERROR_SUCCESS ; 
 char* GetFileAttributesA (char*) ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INSTALLUILEVEL_NONE ; 
 char* INVALID_FILE_ATTRIBUTES ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 char* MsiDoActionA (int /*<<< orphan*/ ,char*) ; 
 char* MsiGetPropertyA (int /*<<< orphan*/ ,char*,char*,int*) ; 
 char* MsiGetTargetPathA (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  MsiSetInternalUI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* MsiSetTargetPathA (int /*<<< orphan*/ ,char*,char*) ; 
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
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int lstrcmpiA (char*,char*) ; 
 char* msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  query_file_path (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void test_settargetpath(void)
{
    char tempdir[MAX_PATH+8], buffer[MAX_PATH], file[MAX_PATH];
    DWORD sz;
    MSIHANDLE hpkg;
    UINT r;
    MSIHANDLE hdb;

    hdb = create_package_db();
    ok ( hdb, "failed to create package database\n" );

    add_directory_entry( hdb, "'TARGETDIR', '', 'SourceDir'" );

    create_component_table( hdb );
    add_component_entry( hdb, "'RootComp', '{83e2694d-0864-4124-9323-6d37630912a1}', 'TARGETDIR', 8, '', 'RootFile'" );
    add_component_entry( hdb, "'TestComp', '{A3FB59C8-C293-4F7E-B8C5-F0E1D8EEE4E5}', 'TestDir', 0, '', 'TestFile'" );

    create_feature_table( hdb );
    add_feature_entry( hdb, "'TestFeature', '', '', '', 0, 1, '', 0" );

    create_feature_components_table( hdb );
    add_feature_components_entry( hdb, "'TestFeature', 'RootComp'" );
    add_feature_components_entry( hdb, "'TestFeature', 'TestComp'" );

    add_directory_entry( hdb, "'TestParent', 'TARGETDIR', 'TestParent'" );
    add_directory_entry( hdb, "'TestDir', 'TestParent', 'TestDir'" );

    create_file_table( hdb );
    add_file_entry( hdb, "'RootFile', 'RootComp', 'rootfile.txt', 0, '', '1033', 8192, 1" );
    add_file_entry( hdb, "'TestFile', 'TestComp', 'testfile.txt', 0, '', '1033', 8192, 1" );

    r = package_from_db( hdb, &hpkg );
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok( r == ERROR_SUCCESS, "failed to create package %u\n", r);

    MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);

    r = MsiDoActionA( hpkg, "CostInitialize");
    ok( r == ERROR_SUCCESS, "cost init failed\n");

    r = MsiDoActionA( hpkg, "FileCost");
    ok( r == ERROR_SUCCESS, "file cost failed\n");

    r = MsiDoActionA( hpkg, "CostFinalize");
    ok( r == ERROR_SUCCESS, "cost finalize failed\n");

    buffer[0] = 0;
    sz = sizeof(buffer);
    r = MsiGetPropertyA( hpkg, "OutOfNoRbDiskSpace", buffer, &sz );
    ok( r == ERROR_SUCCESS, "MsiGetProperty returned %u\n", r );
    trace( "OutOfNoRbDiskSpace = \"%s\"\n", buffer );

    r = MsiSetTargetPathA( 0, NULL, NULL );
    ok( r == ERROR_INVALID_PARAMETER, "wrong return val\n");

    r = MsiSetTargetPathA( 0, "boo", "C:\\bogusx" );
    ok( r == ERROR_INVALID_HANDLE, "wrong return val\n");

    r = MsiSetTargetPathA( hpkg, "boo", NULL );
    ok( r == ERROR_INVALID_PARAMETER, "wrong return val\n");

    r = MsiSetTargetPathA( hpkg, "boo", "c:\\bogusx" );
    ok( r == ERROR_DIRECTORY, "wrong return val\n");

    sz = sizeof tempdir - 1;
    r = MsiGetTargetPathA( hpkg, "TARGETDIR", tempdir, &sz );
    sprintf( file, "%srootfile.txt", tempdir );
    buffer[0] = 0;
    query_file_path( hpkg, "[#RootFile]", buffer );
    ok( r == ERROR_SUCCESS, "failed to get target path: %d\n", r);
    ok( !lstrcmpA(buffer, file), "Expected %s, got %s\n", file, buffer );

    GetTempFileNameA( tempdir, "_wt", 0, buffer );
    sprintf( tempdir, "%s\\subdir", buffer );

    r = MsiSetTargetPathA( hpkg, "TARGETDIR", buffer );
    ok( r == ERROR_SUCCESS || r == ERROR_DIRECTORY,
        "MsiSetTargetPath on file returned %d\n", r );

    r = MsiSetTargetPathA( hpkg, "TARGETDIR", tempdir );
    ok( r == ERROR_SUCCESS || r == ERROR_DIRECTORY,
        "MsiSetTargetPath on 'subdir' of file returned %d\n", r );

    DeleteFileA( buffer );

    r = MsiSetTargetPathA( hpkg, "TARGETDIR", buffer );
    ok( r == ERROR_SUCCESS, "MsiSetTargetPath returned %d\n", r );

    r = GetFileAttributesA( buffer );
    ok ( r == INVALID_FILE_ATTRIBUTES, "file/directory exists after MsiSetTargetPath. Attributes: %08X\n", r );

    r = MsiSetTargetPathA( hpkg, "TARGETDIR", tempdir );
    ok( r == ERROR_SUCCESS, "MsiSetTargetPath on subsubdir returned %d\n", r );

    buffer[0] = 0;
    sz = sizeof buffer - 1;
    lstrcatA( tempdir, "\\" );
    r = MsiGetTargetPathA( hpkg, "TARGETDIR", buffer, &sz );
    ok( r == ERROR_SUCCESS, "failed to get target path: %d\n", r);
    ok( !lstrcmpA(buffer, tempdir), "Expected %s, got %s\n", tempdir, buffer);

    sprintf( file, "%srootfile.txt", tempdir );
    query_file_path( hpkg, "[#RootFile]", buffer );
    ok( !lstrcmpA(buffer, file), "Expected %s, got %s\n", file, buffer);

    buffer[0] = 0;
    sz = sizeof(buffer);
    r = MsiGetPropertyA( hpkg, "TestParent", buffer, &sz );
    ok( r == ERROR_SUCCESS, "MsiGetProperty returned %u\n", r );
    lstrcatA( tempdir, "TestParent\\" );
    ok( !lstrcmpiA(buffer, tempdir), "Expected \"%s\", got \"%s\"\n", tempdir, buffer );

    r = MsiSetTargetPathA( hpkg, "TestParent", "C:\\one\\two" );
    ok( r == ERROR_SUCCESS, "MsiSetTargetPath returned %d\n", r );

    buffer[0] = 0;
    sz = sizeof(buffer);
    r = MsiGetPropertyA( hpkg, "TestParent", buffer, &sz );
    ok( r == ERROR_SUCCESS, "MsiGetProperty returned %u\n", r );
    ok( lstrcmpiA(buffer, "C:\\one\\two\\TestDir\\"),
        "Expected \"C:\\one\\two\\TestDir\\\", got \"%s\"\n", buffer );

    buffer[0] = 0;
    query_file_path( hpkg, "[#TestFile]", buffer );
    ok( !lstrcmpiA(buffer, "C:\\one\\two\\TestDir\\testfile.txt"),
        "Expected C:\\one\\two\\TestDir\\testfile.txt, got %s\n", buffer );

    buffer[0] = 0;
    sz = sizeof buffer - 1;
    r = MsiGetTargetPathA( hpkg, "TestParent", buffer, &sz );
    ok( r == ERROR_SUCCESS, "failed to get target path: %d\n", r);
    ok( !lstrcmpiA(buffer, "C:\\one\\two\\"), "Expected C:\\one\\two\\, got %s\n", buffer);

    r = MsiSetTargetPathA( hpkg, "TestParent", "C:\\one\\two\\three" );
    ok( r == ERROR_SUCCESS, "MsiSetTargetPath returned %d\n", r );

    buffer[0] = 0;
    sz = sizeof buffer - 1;
    r = MsiGetTargetPathA( hpkg, "TestParent", buffer, &sz );
    ok( r == ERROR_SUCCESS, "failed to get target path: %d\n", r);
    ok( !lstrcmpiA(buffer, "C:\\one\\two\\three\\"), "Expected C:\\one\\two\\three\\, got %s\n", buffer);

    r = MsiSetTargetPathA( hpkg, "TestParent", "C:\\\\one\\\\two  " );
    ok( r == ERROR_SUCCESS, "MsiSetTargetPath returned %d\n", r );

    buffer[0] = 0;
    sz = sizeof buffer - 1;
    r = MsiGetTargetPathA( hpkg, "TestParent", buffer, &sz );
    ok( r == ERROR_SUCCESS, "failed to get target path: %d\n", r);
    ok( !lstrcmpiA(buffer, "C:\\one\\two\\"), "Expected \"C:\\one\\two\\\", got %s\n", buffer);

    r = MsiSetTargetPathA( hpkg, "TestParent", "C:\\\\ Program Files \\\\ " );
    ok( r == ERROR_SUCCESS, "MsiSetTargetPath returned %d\n", r );

    buffer[0] = 0;
    sz = sizeof buffer - 1;
    r = MsiGetTargetPathA( hpkg, "TestParent", buffer, &sz );
    ok( r == ERROR_SUCCESS, "failed to get target path: %d\n", r);
    ok( !lstrcmpiA(buffer, "C:\\Program Files\\"), "Expected \"C:\\Program Files\\\", got %s\n", buffer);

    MsiCloseHandle( hpkg );
}