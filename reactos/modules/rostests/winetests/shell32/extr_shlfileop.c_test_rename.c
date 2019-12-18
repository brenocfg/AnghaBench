#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* pFrom; char* pTo; int fFlags; int /*<<< orphan*/ * lpszProgressTitle; int /*<<< orphan*/ * hNameMappings; int /*<<< orphan*/  wFunc; int /*<<< orphan*/ * hwnd; } ;
typedef  TYPE_1__ SHFILEOPSTRUCTA ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int DE_DIFFDIR ; 
 int DE_FILEDESTISFLD ; 
 int DE_MANYSRC1DEST ; 
 int DE_OPCANCELLED ; 
 int ERROR_ACCESS_DENIED ; 
 int ERROR_ALREADY_EXISTS ; 
 int ERROR_CANCELLED ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_GEN_FAILURE ; 
 int ERROR_INVALID_NAME ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int FOF_MULTIDESTFILES ; 
 int FOF_NOCONFIRMATION ; 
 int FOF_NOCONFIRMMKDIR ; 
 int FOF_NOERRORUI ; 
 int FOF_SILENT ; 
 int /*<<< orphan*/  FO_RENAME ; 
 int MAX_PATH ; 
 int SHFileOperationA (TYPE_1__*) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  createTestFile (char*) ; 
 int /*<<< orphan*/  dir_exists (char*) ; 
 int /*<<< orphan*/  file_exists (char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ old_shell32 ; 
 int /*<<< orphan*/  set_curr_dir_path (char*,char*) ; 

__attribute__((used)) static void test_rename(void)
{
    SHFILEOPSTRUCTA shfo, shfo2;
    CHAR from[5*MAX_PATH];
    CHAR to[5*MAX_PATH];
    DWORD retval;

    shfo.hwnd = NULL;
    shfo.wFunc = FO_RENAME;
    shfo.pFrom = from;
    shfo.pTo = to;
    shfo.fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;
    shfo.hNameMappings = NULL;
    shfo.lpszProgressTitle = NULL;

    set_curr_dir_path(from, "test1.txt\0");
    set_curr_dir_path(to, "test4.txt\0");
    retval = SHFileOperationA(&shfo);
    ok(retval == ERROR_ALREADY_EXISTS ||
       retval == DE_FILEDESTISFLD || /* Vista */
       broken(retval == ERROR_INVALID_NAME), /* Win9x, NT4 */
       "Expected ERROR_ALREADY_EXISTS or DE_FILEDESTISFLD, got %d\n", retval);
    ok(file_exists("test1.txt"), "The file is renamed\n");

    set_curr_dir_path(from, "test3.txt\0");
    set_curr_dir_path(to, "test4.txt\\test1.txt\0");
    retval = SHFileOperationA(&shfo);
    if (retval == DE_DIFFDIR)
    {
        /* Vista and W2K8 (broken or new behavior ?) */
        ok(!file_exists("test4.txt\\test1.txt"), "The file is renamed\n");
    }
    else
    {
        ok(retval == ERROR_SUCCESS, "File is renamed moving to other directory\n");
        ok(file_exists("test4.txt\\test1.txt"), "The file is not renamed\n");
    }

    set_curr_dir_path(from, "test1.txt\0test2.txt\0test4.txt\0");
    set_curr_dir_path(to, "test6.txt\0test7.txt\0test8.txt\0");
    retval = SHFileOperationA(&shfo);
    ok(retval == ERROR_GEN_FAILURE ||
       retval == DE_MANYSRC1DEST || /* Vista */
       broken(retval == ERROR_SUCCESS), /* Win9x */
       "Expected ERROR_GEN_FAILURE or DE_MANYSRC1DEST , got %d\n", retval);
    ok(file_exists("test1.txt"), "The file is renamed - many files are specified\n");

    memcpy(&shfo2, &shfo, sizeof(SHFILEOPSTRUCTA));
    shfo2.fFlags |= FOF_MULTIDESTFILES;

    set_curr_dir_path(from, "test1.txt\0test2.txt\0test4.txt\0");
    set_curr_dir_path(to, "test6.txt\0test7.txt\0test8.txt\0");
    retval = SHFileOperationA(&shfo2);
    ok(retval == ERROR_GEN_FAILURE ||
       retval == DE_MANYSRC1DEST || /* Vista */
       broken(retval == ERROR_SUCCESS), /* Win9x */
       "Expected ERROR_GEN_FAILURE or DE_MANYSRC1DEST files, got %d\n", retval);
    ok(file_exists("test1.txt"), "The file is not renamed - many files are specified\n");

    set_curr_dir_path(from, "test1.txt\0");
    set_curr_dir_path(to, "test6.txt\0");
    retval = SHFileOperationA(&shfo);
    ok(retval == ERROR_SUCCESS, "Rename file failed, retval = %d\n", retval);
    ok(!file_exists("test1.txt"), "The file is not renamed\n");
    ok(file_exists("test6.txt"), "The file is not renamed\n");

    set_curr_dir_path(from, "test6.txt\0");
    set_curr_dir_path(to, "test1.txt\0");
    retval = SHFileOperationA(&shfo);
    ok(retval == ERROR_SUCCESS, "Rename file back failed, retval = %d\n", retval);

    set_curr_dir_path(from, "test4.txt\0");
    set_curr_dir_path(to, "test6.txt\0");
    retval = SHFileOperationA(&shfo);
    ok(retval == ERROR_SUCCESS, "Rename dir failed, retval = %d\n", retval);
    ok(!dir_exists("test4.txt"), "The dir is not renamed\n");
    ok(dir_exists("test6.txt"), "The dir is not renamed\n");

    set_curr_dir_path(from, "test6.txt\0");
    set_curr_dir_path(to, "test4.txt\0");
    retval = SHFileOperationA(&shfo);
    ok(retval == ERROR_SUCCESS, "Rename dir back failed, retval = %d\n", retval);
    ok(dir_exists("test4.txt"), "The dir is not renamed\n");

    /* try to rename more than one file to a single file */
    shfo.pFrom = "test1.txt\0test2.txt\0";
    shfo.pTo = "a.txt\0";
    retval = SHFileOperationA(&shfo);
    ok(retval == ERROR_GEN_FAILURE ||
       retval == DE_MANYSRC1DEST || /* Vista */
       broken(retval == ERROR_SUCCESS), /* Win9x */
       "Expected ERROR_GEN_FAILURE or DE_MANYSRC1DEST, got %d\n", retval);
    ok(file_exists("test1.txt"), "Expected test1.txt to exist\n");
    ok(file_exists("test2.txt"), "Expected test2.txt to exist\n");
    ok(!file_exists("a.txt"), "Expected a.txt to not exist\n");

    /* pFrom doesn't exist */
    shfo.pFrom = "idontexist\0";
    shfo.pTo = "newfile\0";
    retval = SHFileOperationA(&shfo);
    ok(retval == 1026 ||
       retval == ERROR_FILE_NOT_FOUND || /* Vista */
       broken(retval == ERROR_SUCCESS), /* NT4 */
       "Expected 1026 or ERROR_FILE_NOT_FOUND, got %d\n", retval);
    ok(!file_exists("newfile"), "Expected newfile to not exist\n");

    /* pTo already exist */
    shfo.pFrom = "test1.txt\0";
    shfo.pTo = "test2.txt\0";
    if (old_shell32)
        shfo.fFlags |= FOF_NOCONFIRMMKDIR;
    retval = SHFileOperationA(&shfo);
    if (retval == ERROR_SUCCESS)
    {
        /* Vista and W2K8 (broken or new behavior ?) */
        createTestFile("test1.txt");
    }
    else
    {
        ok(retval == ERROR_ALREADY_EXISTS ||
           broken(retval == DE_OPCANCELLED) || /* NT4 */
           broken(retval == ERROR_INVALID_NAME), /* Win9x */
           "Expected ERROR_ALREADY_EXISTS, got %d\n", retval);
    }

    /* pFrom is valid, but pTo is empty */
    shfo.pFrom = "test1.txt\0";
    shfo.pTo = "\0";
    retval = SHFileOperationA(&shfo);
    ok(retval == ERROR_CANCELLED ||
       retval == DE_DIFFDIR || /* Vista */
       retval == DE_FILEDESTISFLD || /* Vista, running from c: */
       broken(retval == DE_OPCANCELLED) || /* Win9x */
       broken(retval == 65652), /* NT4 */
       "Expected ERROR_CANCELLED or DE_DIFFDIR, got %u\n", retval);
    ok(file_exists("test1.txt"), "Expected test1.txt to exist\n");

    /* pFrom is empty */
    shfo.pFrom = "\0";
    retval = SHFileOperationA(&shfo);
    ok(retval == ERROR_ACCESS_DENIED ||
       retval == DE_MANYSRC1DEST || /* Vista */
       broken(retval == ERROR_SUCCESS), /* Win9x */
       "Expected ERROR_ACCESS_DENIED or DE_MANYSRC1DEST, got %d\n", retval);

    /* pFrom is NULL, commented out because it crashes on nt 4.0 */
    if (0)
    {
        shfo.pFrom = NULL;
        retval = SHFileOperationA(&shfo);
        ok(retval == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", retval);
    }
}