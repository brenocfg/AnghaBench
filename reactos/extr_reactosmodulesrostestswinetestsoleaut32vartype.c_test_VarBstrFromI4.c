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
typedef  int /*<<< orphan*/  minus_42 ;
typedef  int /*<<< orphan*/  int_min ;
typedef  char WCHAR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  LCID ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LOCALE_NOUSEROVERRIDE ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 scalar_t__ VarBstrFromI4 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_VarBstrFromI4(void)
{
  static const WCHAR int_min[] = { '-','2','1','4','7','4','8','3','6','4','8','\0' };
  static const WCHAR minus_42[] = { '-','4','2','\0' };
  BSTR bstr = NULL;
  HRESULT hres;
  LONG value;
  LCID lcid;

  lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);

#ifdef __REACTOS__
  value = (-2147483647 - 1);
#else
  value = -2147483648;
#endif
  hres = VarBstrFromI4(value, lcid, LOCALE_NOUSEROVERRIDE, &bstr);
  ok(hres == S_OK, "got hres 0x%08x\n", hres);
  if (bstr)
  {
    ok(memcmp(bstr, int_min, sizeof(int_min)) == 0, "string different\n");
    SysFreeString(bstr);
  }

  value = -42;
  hres = VarBstrFromI4(value, lcid, LOCALE_NOUSEROVERRIDE, &bstr);
  ok(hres == S_OK, "got hres 0x%08x\n", hres);
  if (bstr)
  {
    ok(memcmp(bstr, minus_42, sizeof(minus_42)) == 0, "string different\n");
    SysFreeString(bstr);
  }
}