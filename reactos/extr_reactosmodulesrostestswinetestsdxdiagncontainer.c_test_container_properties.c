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
struct property_test {scalar_t__ vt; int /*<<< orphan*/  prop; } ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IDxDiagContainer ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ IDxDiagContainer_GetNumberOfProps (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IDxDiagContainer_GetProp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_container_properties(IDxDiagContainer *container, const struct property_test *property_tests, size_t len)
{
    HRESULT hr;

    /* Check that the container has no properties if there are no properties to examine. */
    if (len == 0)
    {
        DWORD prop_count;

        hr = IDxDiagContainer_GetNumberOfProps(container, &prop_count);
        ok(hr == S_OK, "Expected IDxDiagContainer::GetNumberOfProps to return S_OK, got 0x%08x\n", hr);
        if (hr == S_OK)
            ok(prop_count == 0, "Expected container property count to be zero, got %u\n", prop_count);
    }
    else
    {
        VARIANT var;
        int i;

        VariantInit(&var);

        /* Examine the variant types of obtained property values. */
        for (i = 0; i < len; i++)
        {
            hr = IDxDiagContainer_GetProp(container, property_tests[i].prop, &var);
            ok(hr == S_OK, "[%d] Expected IDxDiagContainer::GetProp to return S_OK for %s, got 0x%08x\n",
               i, wine_dbgstr_w(property_tests[i].prop), hr);

            if (hr == S_OK)
            {
                ok(V_VT(&var) == property_tests[i].vt,
                   "[%d] Expected variant type %d, got %d\n", i, property_tests[i].vt, V_VT(&var));
                trace("%s = %s\n", wine_dbgstr_w(property_tests[i].prop), debugstr_variant(&var));
                VariantClear(&var);
            }
        }
    }
}