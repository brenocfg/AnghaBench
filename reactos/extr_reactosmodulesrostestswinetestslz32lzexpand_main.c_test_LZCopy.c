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
typedef  int /*<<< orphan*/  OFSTRUCT ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LZClose (int) ; 
 int LZCopy (int,int) ; 
 int LZOpenFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_CREATE ; 
 int /*<<< orphan*/  OF_READ ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int ReadFile (scalar_t__,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int WriteFile (scalar_t__,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  compressed_file ; 
 int compressed_file_size ; 
 int /*<<< orphan*/  filename2 ; 
 int /*<<< orphan*/  filename_ ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  uncompressed_data ; 
 int uncompressed_data_size ; 

__attribute__((used)) static void test_LZCopy(void)
{
  HANDLE file;
  DWORD ret;
  int source, dest;
  OFSTRUCT stest, dtest;
  BOOL retok;

  /* Create the compressed file. */
  file = CreateFileA(filename_, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, 0);
  ok(file != INVALID_HANDLE_VALUE, 
     "CreateFileA: error %d\n", GetLastError());
  retok = WriteFile(file, compressed_file, compressed_file_size, &ret, 0);
  ok( retok, "WriteFile error %d\n", GetLastError());
  ok(ret == compressed_file_size, "Wrote wrong number of bytes\n");
  CloseHandle(file);

  source = LZOpenFileA(filename_, &stest, OF_READ);
  ok(source >= 0, "LZOpenFileA failed on compressed file\n");
  dest = LZOpenFileA(filename2, &dtest, OF_CREATE);
  ok(dest >= 0, "LZOpenFileA failed on creating new file %d\n", dest);

  ret = LZCopy(source, dest);
  ok(ret > 0, "LZCopy error\n");

  LZClose(source);
  LZClose(dest);

  file = CreateFileA(filename2, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
  ok(file != INVALID_HANDLE_VALUE,
     "CreateFileA: error %d\n", GetLastError());

  retok = ReadFile(file, buf, uncompressed_data_size*2, &ret, 0);
  ok( retok && ret == uncompressed_data_size, "ReadFile: error %d\n", GetLastError());
  /* Compare what we read with what we think we should read. */
  ok(!memcmp(buf, uncompressed_data, uncompressed_data_size),
     "buffer contents mismatch\n");
  CloseHandle(file);

  ret = DeleteFileA(filename_);
  ok(ret, "DeleteFileA: error %d\n", GetLastError());
  ret = DeleteFileA(filename2);
  ok(ret, "DeleteFileA: error %d\n", GetLastError());
}