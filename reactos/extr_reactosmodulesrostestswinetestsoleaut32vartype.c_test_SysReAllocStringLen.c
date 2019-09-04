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
struct TYPE_3__ {int dwLen; int /*<<< orphan*/  szString; } ;
typedef  char OLECHAR ;
typedef  TYPE_1__* LPINTERNAL_BSTR ;
typedef  char const* BSTR ;

/* Variables and functions */
 TYPE_1__* Get (char const*) ; 
 char* SysAllocStringLen (char const*,int) ; 
 int /*<<< orphan*/  SysFreeString (char const*) ; 
 int SysReAllocStringLen (char const**,char const*,int const) ; 
 int SysStringLen (char const*) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  memset (char const*,int,int const) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SysReAllocStringLen(void)
{
  const OLECHAR szTest[5] = { 'T','e','s','t','\0' };
  const OLECHAR szSmaller[2] = { 'x','\0' };
  const OLECHAR szLarger[7] = { 'L','a','r','g','e','r','\0' };
  BSTR str;

  str = SysAllocStringLen(szTest, 4);
  ok (str != NULL, "Expected non-NULL\n");
  if (str)
  {
    LPINTERNAL_BSTR bstr;
    int changed;

    bstr = Get(str);
    ok (bstr->dwLen == 8, "Expected 8, got %d\n", bstr->dwLen);
    ok (!lstrcmpW(bstr->szString, szTest), "String different\n");

    changed = SysReAllocStringLen(&str, szSmaller, 1);
    ok (changed == 1, "Expected 1, got %d\n", changed);
    /* Vista creates a new string, but older versions reuse the existing string. */
    /*ok (str == oldstr, "Created new string\n");*/
    bstr = Get(str);
    ok (bstr->dwLen == 2, "Expected 2, got %d\n", bstr->dwLen);
    ok (!lstrcmpW(bstr->szString, szSmaller), "String different\n");

    changed = SysReAllocStringLen(&str, szLarger, 6);
    ok (changed == 1, "Expected 1, got %d\n", changed);
    /* Early versions always make new strings rather than resizing */
    /* ok (str == oldstr, "Created new string\n"); */
    bstr = Get(str);
    ok (bstr->dwLen == 12, "Expected 12, got %d\n", bstr->dwLen);
    ok (!lstrcmpW(bstr->szString, szLarger), "String different\n");

    changed = SysReAllocStringLen(&str, str, 6);
    ok (changed == 1, "Expected 1, got %d\n", changed);

    SysFreeString(str);
  }

  /* Windows always returns null terminated strings */
  str = SysAllocStringLen(szTest, 4);
  ok (str != NULL, "Expected non-NULL\n");
  if (str)
  {
    const int CHUNK_SIZE = 64;
    const int STRING_SIZE = 24;
    int changed;
    changed = SysReAllocStringLen(&str, NULL, CHUNK_SIZE);
    ok (changed == 1, "Expected 1, got %d\n", changed);
    ok (str != NULL, "Expected non-NULL\n");
    if (str)
    {
      BSTR oldstr = str;

      /* Filling string */
      memset (str, 0xAB, CHUNK_SIZE * sizeof (OLECHAR));
      /* Checking null terminator */
      changed = SysReAllocStringLen(&str, NULL, STRING_SIZE);
      ok (changed == 1, "Expected 1, got %d\n", changed);
      ok (str != NULL, "Expected non-NULL\n");
      if (str)
      {
        ok (str == oldstr, "Expected reuse of the old string memory\n");
        ok (str[STRING_SIZE] == 0,
            "Expected null terminator, got 0x%04X\n", str[STRING_SIZE]);
        SysFreeString(str);
      }
    }
  }

  /* Some Windows applications use the same pointer for pbstr and psz */
  str = SysAllocStringLen(szTest, 4);
  ok(str != NULL, "Expected non-NULL\n");
  if(str)
  {
      SysReAllocStringLen(&str, str, 1000000);
      ok(SysStringLen(str)==1000000, "Incorrect string length\n");
      ok(!memcmp(szTest, str, 4*sizeof(WCHAR)), "Incorrect string returned\n");

      SysFreeString(str);
  }
}