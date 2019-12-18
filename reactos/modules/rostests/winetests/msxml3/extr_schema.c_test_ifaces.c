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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_XMLSchemaCache60 ; 
 int /*<<< orphan*/  IID_IXMLDOMSchemaCollection2 ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMSchemaCollection2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMSchemaCollection2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_cache_version (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_ifaces(void)
{
    IXMLDOMSchemaCollection2 *cache;
    IUnknown *unk;
    HRESULT hr;

    cache = create_cache_version(60, &IID_IXMLDOMSchemaCollection2);
    if (!cache) return;

    /* CLSID_XMLSchemaCache60 is returned as an interface (the same as IXMLDOMSchemaCollection2). */
    hr = IXMLDOMSchemaCollection2_QueryInterface(cache, &CLSID_XMLSchemaCache60, (void**)&unk);
    ok (hr == S_OK, "Could not get CLSID_XMLSchemaCache60 iface: %08x\n", hr);
    ok (unk == (IUnknown*)cache, "unk != cache\n");

    IUnknown_Release(unk);
    IXMLDOMSchemaCollection2_Release(cache);
}