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
typedef  int UINT ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  char CHAR ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ E_FAIL ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int GetCurrentDirectoryA (int,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 char* lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pDelNode (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delnode_test(void)
{
    HRESULT hr;
    HANDLE hn;
    CHAR currDir[MAX_PATH];
    UINT currDirLen;

    /* Native DelNode apparently does not support relative paths, so we use
       absolute paths for testing */
    currDirLen = GetCurrentDirectoryA(ARRAY_SIZE(currDir), currDir);
    assert(currDirLen > 0 && currDirLen < ARRAY_SIZE(currDir));

    if(currDir[currDirLen - 1] == '\\')
        currDir[--currDirLen] = 0;

    /* Simple tests; these should fail. */
    hr = pDelNode(NULL, 0);
    ok (hr == E_FAIL, "DelNode called with NULL pathname should return E_FAIL\n");
    hr = pDelNode("", 0);
    ok (hr == E_FAIL, "DelNode called with empty pathname should return E_FAIL\n");

    /* Test deletion of a file. */
    hn = CreateFileA("DelNodeTestFile1", GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    assert(hn != INVALID_HANDLE_VALUE);
    CloseHandle(hn);
    hr = pDelNode(lstrcatA(currDir, "\\DelNodeTestFile1"), 0);
    ok (hr == S_OK, "DelNode failed deleting a single file\n");
    currDir[currDirLen] = '\0';

    /* Test deletion of an empty directory. */
    CreateDirectoryA("DelNodeTestDir", NULL);
    hr = pDelNode(lstrcatA(currDir, "\\DelNodeTestDir"), 0);
    ok (hr == S_OK, "DelNode failed deleting an empty directory\n");
    currDir[currDirLen] = '\0';

    /* Test deletion of a directory containing one file. */
    CreateDirectoryA("DelNodeTestDir", NULL);
    hn = CreateFileA("DelNodeTestDir\\DelNodeTestFile1", GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    assert(hn != INVALID_HANDLE_VALUE);
    CloseHandle(hn);
    hr = pDelNode(lstrcatA(currDir, "\\DelNodeTestDir"), 0);
    ok (hr == S_OK, "DelNode failed deleting a directory containing one file\n");
    currDir[currDirLen] = '\0';

    /* Test deletion of a directory containing multiple files. */
    CreateDirectoryA("DelNodeTestDir", NULL);
    hn = CreateFileA("DelNodeTestDir\\DelNodeTestFile1", GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    assert(hn != INVALID_HANDLE_VALUE);
    CloseHandle(hn);
    hn = CreateFileA("DelNodeTestDir\\DelNodeTestFile2", GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    assert(hn != INVALID_HANDLE_VALUE);
    CloseHandle(hn);
    hn = CreateFileA("DelNodeTestDir\\DelNodeTestFile3", GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    assert(hn != INVALID_HANDLE_VALUE);
    CloseHandle(hn);
    hr = pDelNode(lstrcatA(currDir, "\\DelNodeTestDir"), 0);
    ok (hr == S_OK, "DelNode failed deleting a directory containing multiple files\n");
}