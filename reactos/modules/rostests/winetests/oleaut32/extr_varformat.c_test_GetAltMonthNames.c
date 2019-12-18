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
typedef  int /*<<< orphan*/  LPOLESTR ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/ * GetAltMonthNames (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LANG_ARABIC ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_POLISH ; 
 int /*<<< orphan*/  LANG_RUSSIAN ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ARABIC_EGYPT ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GetAltMonthNames(void)
{
    LPOLESTR *str, *str2;
    HRESULT hr;

    str = (void *)0xdeadbeef;
    hr = GetAltMonthNames(0, &str);
    ok(hr == S_OK, "Unexpected return value %08x\n", hr);
    ok(str == NULL, "Got %p\n", str);

    str = (void *)0xdeadbeef;
    hr = GetAltMonthNames(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT), &str);
    ok(hr == S_OK, "Unexpected return value %08x\n", hr);
    ok(str == NULL, "Got %p\n", str);

    str = NULL;
    hr = GetAltMonthNames(MAKELCID(MAKELANGID(LANG_ARABIC, SUBLANG_ARABIC_EGYPT), SORT_DEFAULT), &str);
    ok(hr == S_OK, "Unexpected return value %08x\n", hr);
    ok(str != NULL, "Got %p\n", str);

    str2 = NULL;
    hr = GetAltMonthNames(MAKELCID(MAKELANGID(LANG_ARABIC, SUBLANG_ARABIC_EGYPT), SORT_DEFAULT), &str2);
    ok(hr == S_OK, "Unexpected return value %08x\n", hr);
    ok(str2 == str, "Got %p\n", str2);

    str = NULL;
    hr = GetAltMonthNames(MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT), SORT_DEFAULT), &str);
    ok(hr == S_OK, "Unexpected return value %08x\n", hr);
    ok(str != NULL, "Got %p\n", str);

    str = NULL;
    hr = GetAltMonthNames(MAKELCID(MAKELANGID(LANG_POLISH, SUBLANG_DEFAULT), SORT_DEFAULT), &str);
    ok(hr == S_OK, "Unexpected return value %08x\n", hr);
    ok(str != NULL, "Got %p\n", str);
}