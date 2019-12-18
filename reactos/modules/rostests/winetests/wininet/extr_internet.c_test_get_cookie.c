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
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ InternetGetCookieA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_get_cookie(void)
{
  DWORD len;
  BOOL ret;

  len = 1024;
  SetLastError(0xdeadbeef);
  ret = InternetGetCookieA("http://www.example.com", NULL, NULL, &len);
  ok(!ret && GetLastError() == ERROR_NO_MORE_ITEMS,
    "InternetGetCookie should have failed with %s and error %d\n",
    ret ? "TRUE" : "FALSE", GetLastError());
  ok(!len, "len = %u\n", len);
}