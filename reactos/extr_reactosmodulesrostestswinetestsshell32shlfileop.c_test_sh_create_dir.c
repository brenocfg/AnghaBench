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
typedef  char CHAR ;

/* Variables and functions */
 int ERROR_ALREADY_EXISTS ; 
 int ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int SHCreateDirectoryExA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_exists (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  set_curr_dir_path (char*,char*) ; 

__attribute__((used)) static void test_sh_create_dir(void)
{
    CHAR path[MAX_PATH];
    int ret;

    set_curr_dir_path(path, "testdir2\\test4.txt\0");
    ret = SHCreateDirectoryExA(NULL, path, NULL);
    ok(ERROR_SUCCESS == ret, "SHCreateDirectoryEx failed to create directory recursively, ret = %d\n", ret);
    ok(file_exists("testdir2"), "The first directory is not created\n");
    ok(file_exists("testdir2\\test4.txt"), "The second directory is not created\n");

    ret = SHCreateDirectoryExA(NULL, path, NULL);
    ok(ERROR_ALREADY_EXISTS == ret, "SHCreateDirectoryEx should fail to create existing directory, ret = %d\n", ret);

    ret = SHCreateDirectoryExA(NULL, "c:\\testdir3", NULL);
    ok(ERROR_SUCCESS == ret, "SHCreateDirectoryEx failed to create directory, ret = %d\n", ret);
    ok(file_exists("c:\\testdir3"), "The directory is not created\n");
}