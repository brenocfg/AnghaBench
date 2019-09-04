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
struct TYPE_3__ {int dwLen; int /*<<< orphan*/  szString; } ;
typedef  char OLECHAR ;
typedef  TYPE_1__* LPINTERNAL_BSTR ;
typedef  int DWORD_PTR ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 TYPE_1__* Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SysAllocString(void)
{
  const OLECHAR szTest[5] = { 'T','e','s','t','\0' };
  BSTR str;

  str = SysAllocString(NULL);
  ok (str == NULL, "Expected NULL, got %p\n", str);

  str = SysAllocString(szTest);
  ok (str != NULL, "Expected non-NULL\n");
  if (str)
  {
    LPINTERNAL_BSTR bstr = Get(str);
    DWORD_PTR p = (DWORD_PTR)str;
    int align = sizeof(void *);

    ok (bstr->dwLen == 8, "Expected 8, got %d\n", bstr->dwLen);
    ok (!lstrcmpW(bstr->szString, szTest), "String different\n");
    ok ((p & ~(align-1)) == p, "Not aligned to %d\n", align);
    SysFreeString(str);
  }
}