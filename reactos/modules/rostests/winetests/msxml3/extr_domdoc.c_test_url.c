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
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_get_url (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_FALSE ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_url(void)
{
    IXMLDOMDocument *doc;
    HRESULT hr;
    BSTR s;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_get_url(doc, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    s = (void *)0xdeadbeef;
    hr = IXMLDOMDocument_get_url(doc, &s);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);
    ok(s == NULL, "got %s\n", wine_dbgstr_w(s));

    IXMLDOMDocument_Release(doc);
}