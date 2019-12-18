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
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_HR (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_transformNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 char* omitxmldecl_doc ; 
 char* omitxmldecl_xsl ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 char* xsltext_xsl ; 

__attribute__((used)) static void test_xsltext(void)
{
    IXMLDOMDocument *doc, *doc2;
    VARIANT_BOOL b;
    HRESULT hr;
    BSTR ret;

    doc = create_document(&IID_IXMLDOMDocument);
    doc2 = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_loadXML(doc, _bstr_(xsltext_xsl), &b);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMDocument_loadXML(doc2, _bstr_("<testkey/>"), &b);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMDocument_transformNode(doc2, (IXMLDOMNode*)doc, &ret);
    EXPECT_HR(hr, S_OK);
    ok(!lstrcmpW(ret, _bstr_("testdata")), "transform result %s\n", wine_dbgstr_w(ret));
    SysFreeString(ret);

    /* omit-xml-declaration */
    hr = IXMLDOMDocument_loadXML(doc, _bstr_(omitxmldecl_xsl), &b);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = IXMLDOMDocument_loadXML(doc2, _bstr_(omitxmldecl_doc), &b);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXMLDOMDocument_transformNode(doc2, (IXMLDOMNode*)doc, &ret);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!lstrcmpW(ret, _bstr_("<node>item1</node><node>item2</node>")), "transform result %s\n", wine_dbgstr_w(ret));
    SysFreeString(ret);

    IXMLDOMDocument_Release(doc2);
    IXMLDOMDocument_Release(doc);
    free_bstrs();
}