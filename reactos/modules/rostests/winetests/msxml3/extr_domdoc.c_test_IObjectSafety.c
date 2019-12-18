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
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  IObjectSafety ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_XMLHTTPRequest ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IObjectSafety ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IObjectSafety_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_IObjectSafety_common (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_IObjectSafety(void)
{
    IXMLDOMDocument *doc;
    IObjectSafety *safety;
    HRESULT hr;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_QueryInterface(doc, &IID_IObjectSafety, (void**)&safety);
    ok(hr == S_OK, "ret %08x\n", hr );

    test_IObjectSafety_common(safety);

    IObjectSafety_Release(safety);
    IXMLDOMDocument_Release(doc);

    hr = CoCreateInstance(&CLSID_XMLHTTPRequest, NULL, CLSCTX_INPROC_SERVER,
        &IID_IObjectSafety, (void**)&safety);
    ok(hr == S_OK, "Could not create XMLHTTPRequest instance: %08x\n", hr);

    test_IObjectSafety_common(safety);

    IObjectSafety_Release(safety);

}