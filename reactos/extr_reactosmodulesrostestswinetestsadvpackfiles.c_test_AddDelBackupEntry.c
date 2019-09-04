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
typedef  int /*<<< orphan*/  windir ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AADBE_ADD_ENTRY ; 
 int /*<<< orphan*/  AADBE_DEL_ENTRY ; 
 char* CURR_DIR ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int DeleteFileA (char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 scalar_t__ GetFileAttributesA (char*) ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetFileAttributesA (char*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ broken (int) ; 
 int check_ini_file_attr (char*) ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pAddDelBackupEntry (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_AddDelBackupEntry(void)
{
    BOOL ret;
    HRESULT res;
    CHAR path[MAX_PATH];
    CHAR windir[MAX_PATH];

    lstrcpyA(path, CURR_DIR);
    lstrcatA(path, "\\backup\\basename.INI");

    /* native AddDelBackupEntry crashes if lpcszBaseName is NULL */

    /* try a NULL file list */
    res = pAddDelBackupEntry(NULL, "backup", "basename", AADBE_ADD_ENTRY);
    ok(res == S_OK, "Expected S_OK, got %d\n", res);
    ok(!DeleteFileA(path), "Expected path to not exist\n");

    lstrcpyA(path, CURR_DIR);
    lstrcatA(path, "\\backup\\.INI");

    /* try an empty base name */
    res = pAddDelBackupEntry("one\0two\0three\0", "backup", "", AADBE_ADD_ENTRY);
    ok(res == S_OK, "Expected S_OK, got %d\n", res);
    ok(!DeleteFileA(path), "Expected path to not exist\n");

    lstrcpyA(path, CURR_DIR);
    lstrcatA(path, "\\basename.INI");

    /* try an invalid flag */
    res = pAddDelBackupEntry("one\0two\0three\0", NULL, "basename", 0);
    ok(res == S_OK, "Expected S_OK, got %d\n", res);
    ok(!DeleteFileA(path), "Expected path to not exist\n");

    lstrcpyA(path, "c:\\basename.INI");

    /* create the INF file */
    res = pAddDelBackupEntry("one\0two\0three\0", "c:\\", "basename", AADBE_ADD_ENTRY);
    ok(res == S_OK, "Expected S_OK, got %d\n", res);
    if (GetFileAttributesA(path) != INVALID_FILE_ATTRIBUTES)
    {
        ok(check_ini_file_attr(path), "Expected ini file to be hidden\n");
        ok(DeleteFileA(path), "Expected path to exist\n");
    }
    else
        win_skip("Test file could not be created\n");

    lstrcpyA(path, CURR_DIR);
    lstrcatA(path, "\\backup\\basename.INI");

    /* try to create the INI file in a nonexistent directory */
    RemoveDirectoryA("backup");
    res = pAddDelBackupEntry("one\0two\0three\0", "backup", "basename", AADBE_ADD_ENTRY);
    ok(res == S_OK, "Expected S_OK, got %d\n", res);
    ok(!check_ini_file_attr(path), "Expected ini file to not be hidden\n");
    ok(!DeleteFileA(path), "Expected path to not exist\n");

    /* try an existent, relative backup directory */
    CreateDirectoryA("backup", NULL);
    res = pAddDelBackupEntry("one\0two\0three\0", "backup", "basename", AADBE_ADD_ENTRY);
    ok(res == S_OK, "Expected S_OK, got %d\n", res);
    ok(check_ini_file_attr(path), "Expected ini file to be hidden\n");
    ok(DeleteFileA(path), "Expected path to exist\n");
    RemoveDirectoryA("backup");

    GetWindowsDirectoryA(windir, sizeof(windir));
    sprintf(path, "%s\\basename.INI", windir);

    /* try a NULL backup dir, INI is created in the windows directory */
    res = pAddDelBackupEntry("one\0two\0three\0", NULL, "basename", AADBE_ADD_ENTRY);
    ok(res == S_OK, "Expected S_OK, got %d\n", res);

    /* remove the entries with AADBE_DEL_ENTRY */
    SetFileAttributesA(path, FILE_ATTRIBUTE_NORMAL);
    res = pAddDelBackupEntry("one\0three\0", NULL, "basename", AADBE_DEL_ENTRY);
    SetFileAttributesA(path, FILE_ATTRIBUTE_NORMAL);
    ok(res == S_OK, "Expected S_OK, got %d\n", res);
    ret = DeleteFileA(path);
    ok(ret == TRUE ||
       broken(ret == FALSE), /* win98 */
       "Expected path to exist\n");
}