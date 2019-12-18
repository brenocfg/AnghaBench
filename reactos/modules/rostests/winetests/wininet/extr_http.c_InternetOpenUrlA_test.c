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
typedef  scalar_t__ HINTERNET ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteUrlCacheEntryA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_INTERNET_NAME_NOT_RESOLVED ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  ICU_BROWSER_MODE ; 
 int INTERNET_FLAG_NO_CACHE_WRITE ; 
 int INTERNET_FLAG_RELOAD ; 
 int INTERNET_FLAG_TRANSFER_BINARY ; 
 int /*<<< orphan*/  InternetCanonicalizeUrlA (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InternetCloseHandle (scalar_t__) ; 
 scalar_t__ InternetOpenA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ InternetOpenUrlA (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InternetReadFile (scalar_t__,char*,int,int*) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_URL ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void InternetOpenUrlA_test(void)
{
  HINTERNET myhinternet, myhttp;
  char buffer[0x400];
  DWORD size, readbytes, totalbytes=0;
  BOOL ret;

  ret = DeleteUrlCacheEntryA(TEST_URL);
  ok(ret || GetLastError() == ERROR_FILE_NOT_FOUND,
          "DeleteUrlCacheEntry returned %x, GetLastError() = %d\n", ret, GetLastError());

  myhinternet = InternetOpenA("Winetest",0,NULL,NULL,INTERNET_FLAG_NO_CACHE_WRITE);
  ok((myhinternet != 0), "InternetOpen failed, error %u\n",GetLastError());
  size = 0x400;
  ret = InternetCanonicalizeUrlA(TEST_URL, buffer, &size,ICU_BROWSER_MODE);
  ok( ret, "InternetCanonicalizeUrl failed, error %u\n",GetLastError());

  SetLastError(0);
  myhttp = InternetOpenUrlA(myhinternet, TEST_URL, 0, 0,
			   INTERNET_FLAG_RELOAD|INTERNET_FLAG_NO_CACHE_WRITE|INTERNET_FLAG_TRANSFER_BINARY,0);
  if (GetLastError() == ERROR_INTERNET_NAME_NOT_RESOLVED)
    return; /* WinXP returns this when not connected to the net */
  ok((myhttp != 0),"InternetOpenUrl failed, error %u\n",GetLastError());
  ret = InternetReadFile(myhttp, buffer,0x400,&readbytes);
  ok( ret, "InternetReadFile failed, error %u\n",GetLastError());
  totalbytes += readbytes;
  while (readbytes && InternetReadFile(myhttp, buffer,0x400,&readbytes))
    totalbytes += readbytes;
  trace("read 0x%08x bytes\n",totalbytes);

  InternetCloseHandle(myhttp);
  InternetCloseHandle(myhinternet);

  ret = DeleteUrlCacheEntryA(TEST_URL);
  ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND, "INTERNET_FLAG_NO_CACHE_WRITE flag doesn't work\n");
}