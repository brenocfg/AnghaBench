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
typedef  int /*<<< orphan*/  IXMLDOMElement ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_createElement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMElement_get_tagName (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_get_tagName(void)
{
    IXMLDOMDocument *doc;
    IXMLDOMElement *elem, *elem2;
    HRESULT hr;
    BSTR str;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_createElement(doc, _bstr_("element"), &elem);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXMLDOMElement_get_tagName(elem, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    str = NULL;
    hr = IXMLDOMElement_get_tagName(elem, &str);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!lstrcmpW(str, _bstr_("element")), "got %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    hr = IXMLDOMDocument_createElement(doc, _bstr_("s:element"), &elem2);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    str = NULL;
    hr = IXMLDOMElement_get_tagName(elem2, &str);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!lstrcmpW(str, _bstr_("s:element")), "got %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    IXMLDOMElement_Release(elem);
    IXMLDOMElement_Release(elem2);
    IXMLDOMDocument_Release(doc);
    free_bstrs();
}