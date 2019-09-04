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
struct TYPE_3__ {int /*<<< orphan*/  clsid; int /*<<< orphan*/  value; int /*<<< orphan*/  property; scalar_t__ guid; } ;
typedef  TYPE_1__ property_test_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IXMLDOMDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 scalar_t__ CoCreateInstance (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument2 ; 
 int /*<<< orphan*/  IXMLDOMDocument2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument2_getProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bstr_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_clsid_supported (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 TYPE_1__* properties_test_data ; 

__attribute__((used)) static void test_default_properties(void)
{
    const property_test_t *entry = properties_test_data;

    while (entry->guid)
    {
        IXMLDOMDocument2 *doc;
        VARIANT var;
        HRESULT hr;

        if (!is_clsid_supported(entry->guid, &IID_IXMLDOMDocument2))
        {
            entry++;
            continue;
        }

        hr = CoCreateInstance(entry->guid, NULL, CLSCTX_INPROC_SERVER, &IID_IXMLDOMDocument2, (void**)&doc);
        ok(hr == S_OK, "got 0x%08x\n", hr);

        hr = IXMLDOMDocument2_getProperty(doc, _bstr_(entry->property), &var);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        ok(lstrcmpW(V_BSTR(&var), _bstr_(entry->value)) == 0, "expected %s, for %s\n",
           entry->value, entry->clsid);
        VariantClear(&var);

        IXMLDOMDocument2_Release(doc);

        entry++;
    }
}