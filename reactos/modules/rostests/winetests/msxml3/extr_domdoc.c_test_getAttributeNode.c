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
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  IXMLDOMAttribute ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMAttribute_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMDocument_get_documentElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMElement_getAttributeNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  nonexistent_attrW ; 
 int /*<<< orphan*/  nonexistent_fileW ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* szExampleXML ; 

__attribute__((used)) static void test_getAttributeNode(void)
{
    IXMLDOMAttribute *attr;
    IXMLDOMDocument *doc;
    IXMLDOMElement *elem;
    VARIANT_BOOL v;
    HRESULT hr;
    BSTR str;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_loadXML(doc, _bstr_(szExampleXML), &v);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMDocument_get_documentElement(doc, &elem);
    EXPECT_HR(hr, S_OK);

    str = SysAllocString(nonexistent_fileW);
    hr = IXMLDOMElement_getAttributeNode(elem, str, NULL);
    EXPECT_HR(hr, E_FAIL);

    attr = (IXMLDOMAttribute*)0xdeadbeef;
    hr = IXMLDOMElement_getAttributeNode(elem, str, &attr);
    EXPECT_HR(hr, E_FAIL);
    ok(attr == NULL, "got %p\n", attr);
    SysFreeString(str);

    str = SysAllocString(nonexistent_attrW);
    hr = IXMLDOMElement_getAttributeNode(elem, str, NULL);
    EXPECT_HR(hr, S_FALSE);

    attr = (IXMLDOMAttribute*)0xdeadbeef;
    hr = IXMLDOMElement_getAttributeNode(elem, str, &attr);
    EXPECT_HR(hr, S_FALSE);
    ok(attr == NULL, "got %p\n", attr);
    SysFreeString(str);

    hr = IXMLDOMElement_getAttributeNode(elem, _bstr_("foo:b"), &attr);
    EXPECT_HR(hr, S_OK);
    IXMLDOMAttribute_Release(attr);

    hr = IXMLDOMElement_getAttributeNode(elem, _bstr_("b"), &attr);
    EXPECT_HR(hr, S_FALSE);

    hr = IXMLDOMElement_getAttributeNode(elem, _bstr_("a"), &attr);
    EXPECT_HR(hr, S_OK);
    IXMLDOMAttribute_Release(attr);

    IXMLDOMElement_Release(elem);
    IXMLDOMDocument_Release(doc);
    free_bstrs();
}