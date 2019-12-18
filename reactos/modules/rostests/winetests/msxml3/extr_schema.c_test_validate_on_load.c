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
typedef  scalar_t__ VARIANT_BOOL ;
typedef  int /*<<< orphan*/  IXMLDOMSchemaCollection2 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  IID_IXMLDOMSchemaCollection2 ; 
 int /*<<< orphan*/  IXMLDOMSchemaCollection2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMSchemaCollection2_get_validateOnLoad (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ VARIANT_FALSE ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/ * create_cache_version (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_validate_on_load(void)
{
    IXMLDOMSchemaCollection2 *cache;
    VARIANT_BOOL b;
    HRESULT hr;

    cache = create_cache_version(40, &IID_IXMLDOMSchemaCollection2);
    if (!cache) return;

    hr = IXMLDOMSchemaCollection2_get_validateOnLoad(cache, NULL);
    EXPECT_HR(hr, E_POINTER);

    b = VARIANT_FALSE;
    hr = IXMLDOMSchemaCollection2_get_validateOnLoad(cache, &b);
    EXPECT_HR(hr, S_OK);
    ok(b == VARIANT_TRUE, "got %d\n", b);

    IXMLDOMSchemaCollection2_Release(cache);
}