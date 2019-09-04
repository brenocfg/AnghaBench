#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int dwLen; int /*<<< orphan*/ * szString; } ;
typedef  char OLECHAR ;
typedef  TYPE_1__* LPINTERNAL_BSTR ;
typedef  char* LPCSTR ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 TYPE_1__* Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * SysAllocStringByteLen (char const*,int) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char const*) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SysAllocStringByteLen(void)
{
  const OLECHAR szTest[10] = { 'T','e','s','t','\0' };
  const CHAR szTestA[6] = { 'T','e','s','t','\0','?' };
  char *buf;
  BSTR str;
  int i;

  if (sizeof(void *) == 4)  /* not limited to 0x80000000 on Win64 */
  {
      str = SysAllocStringByteLen(szTestA, 0x80000000);
      ok (str == NULL, "Expected NULL, got %p\n", str);
  }

  str = SysAllocStringByteLen(szTestA, 0xffffffff);
  ok (str == NULL, "Expected NULL, got %p\n", str);

  str = SysAllocStringByteLen(NULL, 0);
  ok (str != NULL, "Expected non-NULL\n");
  if (str)
  {
    LPINTERNAL_BSTR bstr = Get(str);

    ok (bstr->dwLen == 0, "Expected 0, got %d\n", bstr->dwLen);
    ok (!bstr->szString[0], "String not empty\n");
    SysFreeString(str);
  }

  str = SysAllocStringByteLen(szTestA, 4);
  ok (str != NULL, "Expected non-NULL\n");
  if (str)
  {
    LPINTERNAL_BSTR bstr = Get(str);

    ok (bstr->dwLen == 4, "Expected 4, got %d\n", bstr->dwLen);
    ok (!lstrcmpA((LPCSTR)bstr->szString, szTestA), "String different\n");
    SysFreeString(str);
  }

  /* Odd lengths are allocated rounded up, but truncated at the right position */
  str = SysAllocStringByteLen(szTestA, 3);
  ok (str != NULL, "Expected non-NULL\n");
  if (str)
  {
    const CHAR szTestTruncA[4] = { 'T','e','s','\0' };
    LPINTERNAL_BSTR bstr = Get(str);

    ok (bstr->dwLen == 3, "Expected 3, got %d\n", bstr->dwLen);
    ok (!lstrcmpA((LPCSTR)bstr->szString, szTestTruncA), "String different\n");
    ok (!bstr->szString[2], "String not terminated\n");
    SysFreeString(str);
  }

  str = SysAllocStringByteLen((LPCSTR)szTest, 8);
  ok (str != NULL, "Expected non-NULL\n");
  if (str)
  {
    LPINTERNAL_BSTR bstr = Get(str);

    ok (bstr->dwLen == 8, "Expected 8, got %d\n", bstr->dwLen);
    ok (!lstrcmpW(bstr->szString, szTest), "String different\n");
    SysFreeString(str);
  }

  /* Make sure terminating null is aligned properly */
  buf = HeapAlloc(GetProcessHeap(), 0, 1025);
  ok (buf != NULL, "Expected non-NULL\n");
  for (i = 0; i < 1024; i++)
  {
    LPINTERNAL_BSTR bstr;

    str = SysAllocStringByteLen(NULL, i);
    ok (str != NULL, "Expected non-NULL\n");
    bstr = Get(str);
    ok (bstr->dwLen == i, "Expected %d, got %d\n", i, bstr->dwLen);
    ok (!bstr->szString[(i+sizeof(WCHAR)-1)/sizeof(WCHAR)], "String not terminated\n");
    SysFreeString(str);

    memset(buf, 0xaa, 1025);
    str = SysAllocStringByteLen(buf, i);
    ok (str != NULL, "Expected non-NULL\n");
    bstr = Get(str);
    ok (bstr->dwLen == i, "Expected %d, got %d\n", i, bstr->dwLen);
    buf[i] = 0;
    ok (!lstrcmpA((LPCSTR)bstr->szString, buf), "String different\n");
    ok (!bstr->szString[(i+sizeof(WCHAR)-1)/sizeof(WCHAR)], "String not terminated\n");
    SysFreeString(str);
  }
  HeapFree(GetProcessHeap(), 0, buf);
}