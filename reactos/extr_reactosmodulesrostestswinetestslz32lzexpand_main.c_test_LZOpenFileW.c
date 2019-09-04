#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  test ;
typedef  char WCHAR ;
struct TYPE_4__ {int cBytes; int /*<<< orphan*/  szPathName; int /*<<< orphan*/  nErrCode; } ;
typedef  TYPE_1__ OFSTRUCT ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetFileAttributesW (char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  LZClose (scalar_t__) ; 
 scalar_t__ LZERROR_BADINHANDLE ; 
 scalar_t__ LZOpenFileW (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OF_CREATE ; 
 int /*<<< orphan*/  OF_DELETE ; 
 int /*<<< orphan*/  OF_EXIST ; 
 int /*<<< orphan*/  OF_READ ; 
 int /*<<< orphan*/  OF_READWRITE ; 
 int /*<<< orphan*/  OF_WRITE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 char* filenameW_ ; 
 int /*<<< orphan*/  filename_ ; 
 int /*<<< orphan*/  full_file_path_name_in_a_CWD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lstrcmpA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_LZOpenFileW_existing_compressed () ; 
 int /*<<< orphan*/  test_LZOpenFileW_nonexisting_compressed () ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_LZOpenFileW(void)
{
  OFSTRUCT test;
  DWORD retval;
  INT file;
  static WCHAR badfilenameW[] = {'b','a','d','f','i','l','e','n','a','m','e','.','x','t','n',0};
  char expected[MAX_PATH];

  SetLastError(0xfaceabee);
  /* Check for nonexistent file. */
  file = LZOpenFileW(badfilenameW, &test, OF_READ);
  if(GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
  {
    win_skip("LZOpenFileW call is not implemented\n");
    return;
  }
  ok(GetLastError() == ERROR_FILE_NOT_FOUND,
     "GetLastError() returns %d\n", GetLastError());
  ok(file == LZERROR_BADINHANDLE, "LZOpenFileW succeeded on nonexistent file\n");
  LZClose(file);

  memset(&test, 0xA5, sizeof(test));
  full_file_path_name_in_a_CWD(filename_, expected, FALSE);

  /* Create an empty file. */
  file = LZOpenFileW(filenameW_, &test, OF_CREATE);
  ok(file >= 0, "LZOpenFile failed on creation\n");
  ok(test.cBytes == sizeof(OFSTRUCT),
     "LZOpenFileW set test.cBytes to %d\n", test.cBytes);
  ok(test.nErrCode == ERROR_SUCCESS,
     "LZOpenFileW set test.nErrCode to %d\n", test.nErrCode);
  ok(lstrcmpA(test.szPathName, expected) == 0,
     "LZOpenFileW returned '%s', but was expected to return '%s'\n",
     test.szPathName, expected);
  LZClose(file);

  retval = GetFileAttributesW(filenameW_);
  ok(retval != INVALID_FILE_ATTRIBUTES, "GetFileAttributes: error %d\n", 
    GetLastError());

  /* Check various opening options: */
  memset(&test, 0xA5, sizeof(test));

  /* a, for reading. */
  file = LZOpenFileW(filenameW_, &test, OF_READ);
  ok(file >= 0, "LZOpenFileW failed on read\n");
  ok(test.cBytes == sizeof(OFSTRUCT),
     "LZOpenFileW set test.cBytes to %d\n", test.cBytes);
  ok(test.nErrCode == ERROR_SUCCESS,
     "LZOpenFileW set test.nErrCode to %d\n", test.nErrCode);
  ok(lstrcmpA(test.szPathName, expected) == 0,
     "LZOpenFileW returned '%s', but was expected to return '%s'\n",
     test.szPathName, expected);
  LZClose(file);

  memset(&test, 0xA5, sizeof(test));

  /* b, for writing. */
  file = LZOpenFileW(filenameW_, &test, OF_WRITE);
  ok(file >= 0, "LZOpenFileW failed on write\n");
  ok(test.cBytes == sizeof(OFSTRUCT),
     "LZOpenFileW set test.cBytes to %d\n", test.cBytes);
  ok(test.nErrCode == ERROR_SUCCESS,
     "LZOpenFileW set test.nErrCode to %d\n", test.nErrCode);
  ok(lstrcmpA(test.szPathName, expected) == 0,
     "LZOpenFileW returned '%s', but was expected to return '%s'\n",
     test.szPathName, expected);
  LZClose(file);

  memset(&test, 0xA5, sizeof(test));

  /* c, for reading and writing. */
  file = LZOpenFileW(filenameW_, &test, OF_READWRITE);
  ok(file >= 0, "LZOpenFileW failed on read/write\n");
  ok(test.cBytes == sizeof(OFSTRUCT),
     "LZOpenFileW set test.cBytes to %d\n", test.cBytes);
  ok(test.nErrCode == ERROR_SUCCESS,
     "LZOpenFileW set test.nErrCode to %d\n", test.nErrCode);
  ok(lstrcmpA(test.szPathName, expected) == 0,
     "LZOpenFileW returned '%s', but was expected to return '%s'\n",
     test.szPathName, expected);
  LZClose(file);

  memset(&test, 0xA5, sizeof(test));

  /* d, for checking file existence. */
  file = LZOpenFileW(filenameW_, &test, OF_EXIST);
  ok(file >= 0, "LZOpenFileW failed on read/write\n");
  ok(test.cBytes == sizeof(OFSTRUCT),
     "LZOpenFileW set test.cBytes to %d\n", test.cBytes);
  ok(test.nErrCode == ERROR_SUCCESS,
     "LZOpenFileW set test.nErrCode to %d\n", test.nErrCode);
  ok(lstrcmpA(test.szPathName, expected) == 0,
     "LZOpenFileW returned '%s', but was expected to return '%s'\n",
     test.szPathName, expected);
  LZClose(file);

  memset(&test, 0xA5, sizeof(test));

  /* Delete the file then make sure it doesn't exist anymore. */
  file = LZOpenFileW(filenameW_, &test, OF_DELETE);
  ok(file >= 0, "LZOpenFileW failed on delete\n");
  ok(test.cBytes == sizeof(OFSTRUCT),
     "LZOpenFileW set test.cBytes to %d\n", test.cBytes);
  ok(test.nErrCode == ERROR_SUCCESS,
     "LZOpenFileW set test.nErrCode to %d\n", test.nErrCode);
  ok(lstrcmpA(test.szPathName, expected) == 0,
     "LZOpenFileW returned '%s', but was expected to return '%s'\n",
     test.szPathName, expected);
  LZClose(file);

  retval = GetFileAttributesW(filenameW_);
  ok(retval == INVALID_FILE_ATTRIBUTES, 
     "GetFileAttributesW succeeded on deleted file\n");

  test_LZOpenFileW_existing_compressed();
  test_LZOpenFileW_nonexisting_compressed();
}