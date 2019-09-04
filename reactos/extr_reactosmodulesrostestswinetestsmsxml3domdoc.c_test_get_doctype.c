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
typedef  char WCHAR ;
typedef  scalar_t__ VARIANT_BOOL ;
typedef  int /*<<< orphan*/  IXMLDOMDocumentType ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMDocumentType_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IXMLDOMDocumentType_get_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IXMLDOMDocumentType_get_nodeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IXMLDOMDocument_get_doctype (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * S_FALSE ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/  _bstr_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  szEmailXML ; 
 int /*<<< orphan*/ * wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_get_doctype(void)
{
    static const WCHAR emailW[] = {'e','m','a','i','l',0};
    IXMLDOMDocumentType *doctype;
    IXMLDOMDocument *doc;
    VARIANT_BOOL b;
    HRESULT hr;
    BSTR s;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_get_doctype(doc, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    doctype = (void*)0xdeadbeef;
    hr = IXMLDOMDocument_get_doctype(doc, &doctype);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);
    ok(doctype == NULL, "got %p\n", doctype);

    hr = IXMLDOMDocument_loadXML(doc, _bstr_(szEmailXML), &b);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(b == VARIANT_TRUE, "failed to load XML string\n");

    doctype = NULL;
    hr = IXMLDOMDocument_get_doctype(doc, &doctype);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(doctype != NULL, "got %p\n", doctype);

    hr = IXMLDOMDocumentType_get_name(doctype, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = IXMLDOMDocumentType_get_name(doctype, &s);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!lstrcmpW(emailW, s), "got name %s\n", wine_dbgstr_w(s));
    SysFreeString(s);

    hr = IXMLDOMDocumentType_get_nodeName(doctype, &s);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!lstrcmpW(emailW, s), "got name %s\n", wine_dbgstr_w(s));
    SysFreeString(s);

    IXMLDOMDocumentType_Release(doctype);
    IXMLDOMDocument_Release(doc);
}