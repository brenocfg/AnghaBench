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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_StdFont ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int StringFromGUID2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wszCLSID_StdFont ; 

__attribute__((used)) static void test_StringFromGUID2(void)
{
  WCHAR str[50];
  int len;

  /* invalid pointer */
  SetLastError(0xdeadbeef);
  len = StringFromGUID2(NULL,str,50);
  ok(len == 0, "len: %d (expected 0)\n", len);
  ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %x\n", GetLastError());

  /* Test corner cases for buffer size */
  len = StringFromGUID2(&CLSID_StdFont,str,50);
  ok(len == 39, "len: %d (expected 39)\n", len);
  ok(!lstrcmpiW(str, wszCLSID_StdFont),"string wasn't equal for CLSID_StdFont\n");

  memset(str,0,sizeof str);
  len = StringFromGUID2(&CLSID_StdFont,str,39);
  ok(len == 39, "len: %d (expected 39)\n", len);
  ok(!lstrcmpiW(str, wszCLSID_StdFont),"string wasn't equal for CLSID_StdFont\n");

  len = StringFromGUID2(&CLSID_StdFont,str,38);
  ok(len == 0, "len: %d (expected 0)\n", len);

  len = StringFromGUID2(&CLSID_StdFont,str,30);
  ok(len == 0, "len: %d (expected 0)\n", len);
}