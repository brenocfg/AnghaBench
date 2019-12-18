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
struct TYPE_3__ {int dwLen; int /*<<< orphan*/ * szString; } ;
typedef  char OLECHAR ;
typedef  TYPE_1__* LPINTERNAL_BSTR ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 TYPE_1__* Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SysAllocStringLen (char const*,int) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SysAllocStringLen(void)
{
  const OLECHAR szTest[5] = { 'T','e','s','t','\0' };
  BSTR str;

  /* Very early native dlls do not limit the size of strings, so skip this test */
  if (0)
  {
  str = SysAllocStringLen(szTest, 0x80000000);
  ok (str == NULL, "Expected NULL, got %p\n", str);
  }
  
  str = SysAllocStringLen(NULL, 0);
  ok (str != NULL, "Expected non-NULL\n");
  if (str)
  {
    LPINTERNAL_BSTR bstr = Get(str);

    ok (bstr->dwLen == 0, "Expected 0, got %d\n", bstr->dwLen);
    ok (!bstr->szString[0], "String not empty\n");
    SysFreeString(str);
  }

  str = SysAllocStringLen(szTest, 4);
  ok (str != NULL, "Expected non-NULL\n");
  if (str)
  {
    LPINTERNAL_BSTR bstr = Get(str);

    ok (bstr->dwLen == 8, "Expected 8, got %d\n", bstr->dwLen);
    ok (!lstrcmpW(bstr->szString, szTest), "String different\n");
    SysFreeString(str);
  }
}