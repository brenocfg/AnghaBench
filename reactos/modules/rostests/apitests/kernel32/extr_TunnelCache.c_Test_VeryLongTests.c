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
typedef  int UCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateDirectory (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFile (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFile (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetCurrentDirectory (int,char*) ; 
 scalar_t__ GetFileTime (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ MoveFile (char*,char*) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  RemoveDirectory (char*) ; 
 int RtlCompareMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SetCurrentDirectory (char*) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static
void
Test_VeryLongTests(void)
{
    UCHAR i = 0;
    HANDLE hFile;
    CHAR TestDir[] = "XTestDirTunnelCache";
    CHAR OldDir[MAX_PATH];
    FILETIME FileTime, File1Time;

    win_skip("Too long, see: ROSTESTS-177\n");
    return;

    /* Create a blank test directory */
    if (GetCurrentDirectory(MAX_PATH, OldDir) == 0)
    {
        win_skip("No test directory available\n");
        return;
    }

    /* Create a blank test directory */
    for (; i < 10; ++i)
    {
        TestDir[0] = '0' + i;
        if (CreateDirectory(TestDir, NULL))
        {
            if (SetCurrentDirectory(TestDir) == 0)
            {
                RemoveDirectory(TestDir);
                win_skip("No test directory available\n");
                return;
            }
	
            break;
        }
    }

    if (i == 10)
    {
        win_skip("No test directory available\n");
        return;
    }

    hFile = CreateFile("file1",
                       GENERIC_READ | GENERIC_WRITE,
                       0, NULL,
                       CREATE_NEW,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);
    ok(hFile != INVALID_HANDLE_VALUE, "CreateFile() failed\n");
    ok(GetFileTime(hFile, &FileTime, NULL, NULL) != FALSE, "GetFileTime() failed\n");
    CloseHandle(hFile);

    /* Wait a least 10ms (resolution of FAT) */
    /* XXX: Increased to 1s for ReactOS... */
    Sleep(1000);

    hFile = CreateFile("file2",
                       GENERIC_READ | GENERIC_WRITE,
                       0, NULL,
                       CREATE_NEW,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);
    ok(hFile != INVALID_HANDLE_VALUE, "CreateFile() failed\n");
    CloseHandle(hFile);

    ok(MoveFile("file1", "file") != FALSE, "MoveFile() failed\n");
    /* Sleep over cache expiry */
    /* FIXME: Query correct value from registry if it exists:
     * \HKLM\System\CurrentControlSet\Control\FileSystem\MaximumTunnelEntryAgeInSeconds */
    Sleep(16000);
    ok(MoveFile("file2", "file1") != FALSE, "MoveFile() failed\n");

    hFile = CreateFile("file1",
                       GENERIC_READ,
                       0, NULL,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);
    ok(hFile != INVALID_HANDLE_VALUE, "CreateFile() failed\n");
    ok(GetFileTime(hFile, &File1Time, NULL, NULL) != FALSE, "GetFileTime() failed\n");
    CloseHandle(hFile);

    ok(RtlCompareMemory(&FileTime, &File1Time, sizeof(FILETIME)) != sizeof(FILETIME), "Tunnel cache still in action?\n");

    DeleteFile("file2");
    DeleteFile("file1");
    DeleteFile("file");

    SetCurrentDirectory(OldDir);
    RemoveDirectory(TestDir);
}