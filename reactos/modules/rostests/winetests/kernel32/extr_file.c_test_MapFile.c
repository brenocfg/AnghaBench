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
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileMappingA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char*) ; 
 int DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_FILE_INVALID ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 scalar_t__ broken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int test_Mapfile_createtemp (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_MapFile(void)
{
    HANDLE handle;
    HANDLE hmap;

    ok(test_Mapfile_createtemp(&handle), "Couldn't create test file.\n");

    hmap = CreateFileMappingA( handle, NULL, PAGE_READWRITE, 0, 0x1000, "named_file_map" );
    ok( hmap != NULL, "mapping should work, I named it!\n" );

    ok( CloseHandle( hmap ), "can't close mapping handle\n");

    /* We have to close file before we try new stuff with mapping again.
       Else we would always succeed on XP or block descriptors on 95. */
    hmap = CreateFileMappingA( handle, NULL, PAGE_READWRITE, 0, 0, NULL );
    ok( hmap != NULL, "We should still be able to map!\n" );
    ok( CloseHandle( hmap ), "can't close mapping handle\n");
    ok( CloseHandle( handle ), "can't close file handle\n");
    handle = NULL;

    ok(test_Mapfile_createtemp(&handle), "Couldn't create test file.\n");

    hmap = CreateFileMappingA( handle, NULL, PAGE_READWRITE, 0, 0, NULL );
    ok( hmap == NULL, "mapped zero size file\n");
    ok( GetLastError() == ERROR_FILE_INVALID, "not ERROR_FILE_INVALID\n");

    hmap = CreateFileMappingA( handle, NULL, PAGE_READWRITE, 0x80000000, 0, NULL );
    ok( hmap == NULL || broken(hmap != NULL) /* NT4 */, "mapping should fail\n");
    /* GetLastError() varies between win9x and WinNT and also depends on the filesystem */
    if ( hmap )
        CloseHandle( hmap );

    hmap = CreateFileMappingA( handle, NULL, PAGE_READWRITE, 0x80000000, 0x10000, NULL );
    ok( hmap == NULL || broken(hmap != NULL) /* NT4 */, "mapping should fail\n");
    /* GetLastError() varies between win9x and WinNT and also depends on the filesystem */
    if ( hmap )
        CloseHandle( hmap );

    /* On XP you can now map again, on Win 95 you cannot. */

    ok( CloseHandle( handle ), "can't close file handle\n");
    ok( DeleteFileA( filename ), "DeleteFile failed after map\n" );
}