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
typedef  int /*<<< orphan*/  VARIANT_BOOL ;
typedef  int /*<<< orphan*/  IXMLDOMElement ;
typedef  int /*<<< orphan*/  IXMLDOMDocumentFragment ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  IXMLDOMComment ;
typedef  int /*<<< orphan*/  IXMLDOMCDATASection ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMCDATASection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IXMLDOMCDATASection_get_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMComment_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IXMLDOMComment_get_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMDocumentFragment_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IXMLDOMDocumentFragment_get_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IXMLDOMDocument_createCDATASection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IXMLDOMDocument_createComment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IXMLDOMDocument_createDocumentFragment (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IXMLDOMDocument_createElement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IXMLDOMDocument_get_documentElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IXMLDOMDocument_get_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IXMLDOMElement_get_namespaceURI (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IXMLDOMElement_get_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * S_FALSE ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 char* get_prefix_doc ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_get_prefix(void)
{
    IXMLDOMDocumentFragment *fragment;
    IXMLDOMCDATASection *cdata;
    IXMLDOMElement *element;
    IXMLDOMComment *comment;
    IXMLDOMDocument *doc;
    VARIANT_BOOL b;
    HRESULT hr;
    BSTR str;

    doc = create_document(&IID_IXMLDOMDocument);

    /* nodes that can't support prefix */
    /* 1. document */
    str = (void*)0xdeadbeef;
    hr = IXMLDOMDocument_get_prefix(doc, &str);
    EXPECT_HR(hr, S_FALSE);
    ok(str == NULL, "got %p\n", str);

    hr = IXMLDOMDocument_get_prefix(doc, NULL);
    EXPECT_HR(hr, E_INVALIDARG);

    /* 2. cdata */
    hr = IXMLDOMDocument_createCDATASection(doc, NULL, &cdata);
    ok(hr == S_OK, "got %08x\n", hr );

    str = (void*)0xdeadbeef;
    hr = IXMLDOMCDATASection_get_prefix(cdata, &str);
    ok(hr == S_FALSE, "got %08x\n", hr);
    ok( str == 0, "got %p\n", str);

    hr = IXMLDOMCDATASection_get_prefix(cdata, NULL);
    ok(hr == E_INVALIDARG, "got %08x\n", hr);
    IXMLDOMCDATASection_Release(cdata);

    /* 3. comment */
    hr = IXMLDOMDocument_createComment(doc, NULL, &comment);
    ok(hr == S_OK, "got %08x\n", hr );

    str = (void*)0xdeadbeef;
    hr = IXMLDOMComment_get_prefix(comment, &str);
    ok(hr == S_FALSE, "got %08x\n", hr);
    ok( str == 0, "got %p\n", str);

    hr = IXMLDOMComment_get_prefix(comment, NULL);
    ok(hr == E_INVALIDARG, "got %08x\n", hr);
    IXMLDOMComment_Release(comment);

    /* 4. fragment */
    hr = IXMLDOMDocument_createDocumentFragment(doc, &fragment);
    ok(hr == S_OK, "got %08x\n", hr );

    str = (void*)0xdeadbeef;
    hr = IXMLDOMDocumentFragment_get_prefix(fragment, &str);
    ok(hr == S_FALSE, "got %08x\n", hr);
    ok( str == 0, "got %p\n", str);

    hr = IXMLDOMDocumentFragment_get_prefix(fragment, NULL);
    ok(hr == E_INVALIDARG, "got %08x\n", hr);
    IXMLDOMDocumentFragment_Release(fragment);

    /* no prefix */
    hr = IXMLDOMDocument_createElement(doc, _bstr_("elem"), &element);
    ok( hr == S_OK, "got 0x%08x\n", hr);

    hr = IXMLDOMElement_get_prefix(element, NULL);
    ok( hr == E_INVALIDARG, "got 0x%08x\n", hr);

    str = (void*)0xdeadbeef;
    hr = IXMLDOMElement_get_prefix(element, &str);
    ok( hr == S_FALSE, "got 0x%08x\n", hr);
    ok( str == 0, "got %p\n", str);

    IXMLDOMElement_Release(element);

    /* with prefix */
    hr = IXMLDOMDocument_createElement(doc, _bstr_("a:elem"), &element);
    ok( hr == S_OK, "got 0x%08x\n", hr);

    str = (void*)0xdeadbeef;
    hr = IXMLDOMElement_get_prefix(element, &str);
    ok( hr == S_OK, "got 0x%08x\n", hr);
    ok( lstrcmpW(str, _bstr_("a")) == 0, "expected prefix \"a\"\n");
    SysFreeString(str);

    str = (void*)0xdeadbeef;
    hr = IXMLDOMElement_get_namespaceURI(element, &str);
    ok( hr == S_FALSE, "got 0x%08x\n", hr);
    ok( str == 0, "got %p\n", str);

    IXMLDOMElement_Release(element);

    hr = IXMLDOMDocument_loadXML(doc, _bstr_(get_prefix_doc), &b);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMDocument_get_documentElement(doc, &element);
    EXPECT_HR(hr, S_OK);

    str = (void*)0xdeadbeef;
    hr = IXMLDOMElement_get_prefix(element, &str);
    EXPECT_HR(hr, S_FALSE);
    ok(str == NULL, "got %p\n", str);

    str = (void*)0xdeadbeef;
    hr = IXMLDOMElement_get_namespaceURI(element, &str);
    EXPECT_HR(hr, S_FALSE);
    ok(str == NULL, "got %s\n", wine_dbgstr_w(str));

    IXMLDOMDocument_Release(doc);
    free_bstrs();
}