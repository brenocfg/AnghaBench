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
struct assoc_test_struct {void* extension; void* type; void* perceived; void* flags; int /*<<< orphan*/  hr; } ;
typedef  void* PERCEIVED ;
typedef  void* LPWSTR ;
typedef  void* INT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (void*) ; 
 int /*<<< orphan*/  SHStrDupA (void*,void**) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ StrCmpIW (void*,void*) ; 
 scalar_t__ broken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_hr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,void*,void*,...) ; 
 int /*<<< orphan*/  pAssocGetPerceivedType (void*,void**,void**,void**) ; 
 void* wine_dbgstr_w (void*) ; 

__attribute__((used)) static void test_assoc_one(const struct assoc_test_struct* test)
{
    LPWSTR extension, type_expected, type_returned;
    PERCEIVED perceived;
    HRESULT hr;
    INT flags;

    /* if SHStrDupA receives a nullptr as input, it will null the output */
    SHStrDupA(test->extension, &extension);
    SHStrDupA(test->type, &type_expected);

    perceived = 0xdeadbeef;
    flags = 0xdeadbeef;

    hr = pAssocGetPerceivedType(extension, &perceived, &flags, NULL);
    expect_hr(type_expected ? S_OK : test->hr, hr);
    ok(perceived == test->perceived, "%s: got perceived 0x%x, expected 0x%x\n",
       test->extension, perceived, test->perceived);
    ok(flags == test->flags, "%s: got flags 0x%x, expected 0x%x\n",
       test->extension, flags, test->flags);

    type_returned = (void *)0xdeadbeef;
    perceived = 0xdeadbeef;
    flags = 0xdeadbeef;

    hr = pAssocGetPerceivedType(extension, &perceived, &flags, &type_returned);
    expect_hr(type_expected ? S_OK : test->hr, hr);
    ok(perceived == test->perceived, "%s: got perceived 0x%x, expected 0x%x\n",
       test->extension, perceived, test->perceived);
    ok(flags == test->flags, "%s: got flags 0x%x, expected 0x%x\n",
       test->extension, flags, test->flags);

    if (!type_expected)
    {
        ok(type_returned == (void *)0xdeadbeef || broken(type_returned == NULL) /* Win 8 */,
           "%s: got type %p, expected 0xdeadbeef\n", test->extension, type_returned);
    }
    else if (type_returned == (void *)0xdeadbeef)
    {
        ok(type_returned != (void *)0xdeadbeef, "%s: got type %p, expected '%s'\n",
           test->extension, type_returned, test->type);
    }
    else
    {
        ok(StrCmpIW(type_expected, type_returned) == 0, "%s: got type %s, expected '%s'\n",
           test->extension, wine_dbgstr_w(type_returned), test->type);
    }

    CoTaskMemFree(type_returned);
    CoTaskMemFree(extension);
    CoTaskMemFree(type_expected);
}