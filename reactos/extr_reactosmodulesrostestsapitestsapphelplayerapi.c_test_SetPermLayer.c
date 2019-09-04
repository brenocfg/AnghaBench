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
typedef  int /*<<< orphan*/  file ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLongPathNameA (char*,char*,int) ; 
 int /*<<< orphan*/  GetTempPathA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  PathAppendA (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ setLayerValue (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_SdbSetPermLayerKeysLevel (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_SetPermLayerStateLevel (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_SetPermLayer(void)
{
    char file[MAX_PATH + 20], tmp[MAX_PATH + 20];
    HANDLE hfile;

    GetTempPathA(MAX_PATH, tmp);
    GetLongPathNameA(tmp, file, sizeof(file));
    PathAppendA(file, "test_file.exe");

    hfile = CreateFileA(file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    ok(hfile != INVALID_HANDLE_VALUE, "CreateFile failed for '%s'\n", file);
    if (hfile == INVALID_HANDLE_VALUE)
    {
        skip("Running these tests is useless without a file present\n");
        return;
    }
    CloseHandle(hfile);

    if (setLayerValue(FALSE, file, NULL))
    {
        test_SdbSetPermLayerKeysLevel(FALSE, file);
        test_SetPermLayerStateLevel(FALSE, file);
    }
    else
    {
        skip("Skipping SetPermLayerStateLevel tests for User, because I cannot prepare the environment\n");
    }
    if (setLayerValue(TRUE, file, NULL))
    {
        test_SdbSetPermLayerKeysLevel(TRUE, file);
        test_SetPermLayerStateLevel(TRUE, file);
    }
    else
    {
        skip("Skipping SetPermLayerStateLevel tests for Machine (HKLM), because I cannot prepare the environment\n");
    }
    ok(DeleteFileA(file), "DeleteFile failed....\n");
}