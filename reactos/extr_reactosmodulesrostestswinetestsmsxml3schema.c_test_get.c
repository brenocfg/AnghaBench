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
typedef  int /*<<< orphan*/  IXMLDOMSchemaCollection2 ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_HR (scalar_t__,scalar_t__) ; 
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  IID_IXMLDOMSchemaCollection2 ; 
 int /*<<< orphan*/  IXMLDOMSchemaCollection2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMSchemaCollection2_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * _bstr_ (char*) ; 
 int /*<<< orphan*/ * create_cache_version (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_get(void)
{
    IXMLDOMSchemaCollection2 *cache;
    IXMLDOMNode *node;
    HRESULT hr;

    cache = create_cache_version(60, &IID_IXMLDOMSchemaCollection2);
    if (!cache) return;

    hr = IXMLDOMSchemaCollection2_get(cache, NULL, NULL);
    ok(hr == E_NOTIMPL || hr == E_POINTER /* win8 */, "got %08x\n", hr);

    hr = IXMLDOMSchemaCollection2_get(cache, _bstr_("uri"), &node);
    EXPECT_HR(hr, E_NOTIMPL);

    IXMLDOMSchemaCollection2_Release(cache);

    cache = create_cache_version(40, &IID_IXMLDOMSchemaCollection2);
    if (!cache) return;

    hr = IXMLDOMSchemaCollection2_get(cache, NULL, NULL);
    EXPECT_HR(hr, E_POINTER);

    hr = IXMLDOMSchemaCollection2_get(cache, _bstr_("uri"), &node);
    EXPECT_HR(hr, S_OK);

    IXMLDOMSchemaCollection2_Release(cache);
    free_bstrs();
}