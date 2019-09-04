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
typedef  scalar_t__ VARIANT_BOOL ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMElement ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  IXMLDOMAttribute ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_HR (scalar_t__,scalar_t__) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IID_IXMLDOMElement ; 
 int /*<<< orphan*/  IXMLDOMAttribute_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMAttribute_get_nodeName (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMAttribute_get_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_get_namespaceURI (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ IXMLDOMDocument_selectSingleNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMElement_getAttributeNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_firstChild (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNode_get_namespaceURI (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNode_get_nodeName (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNode_get_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/  _bstr_ (char const*) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_namespaces_basic(void)
{
    static const CHAR namespaces_xmlA[] =
        "<?xml version=\"1.0\"?>\n"
        "<XMI xmi.version=\"1.1\" xmlns:Model=\"http://omg.org/mof.Model/1.3\">"
        "  <XMI.content>"
        "    <Model:Package name=\"WinePackage\" Model:name2=\"name2 attr\" />"
        "  </XMI.content>"
        "</XMI>";

    IXMLDOMDocument *doc;
    IXMLDOMElement *elem;
    IXMLDOMNode *node;

    VARIANT_BOOL b;
    HRESULT hr;
    BSTR str;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_loadXML(doc, _bstr_(namespaces_xmlA), &b);
    EXPECT_HR(hr, S_OK);
    ok(b == VARIANT_TRUE, "got %d\n", b);

    str = (void *)0xdeadbeef;
    hr = IXMLDOMDocument_get_namespaceURI(doc, &str);
    EXPECT_HR(hr, S_FALSE);
    ok(str == NULL, "got %p\n", str);

    hr = IXMLDOMDocument_selectSingleNode(doc, _bstr_("//XMI.content"), &node );
    EXPECT_HR(hr, S_OK);
    if(hr == S_OK)
    {
        IXMLDOMAttribute *attr;
        IXMLDOMNode *node2;

        hr = IXMLDOMNode_get_firstChild(node, &node2);
        EXPECT_HR(hr, S_OK);
        ok(node2 != NULL, "got %p\n", node2);

        /* Test get_prefix */
        hr = IXMLDOMNode_get_prefix(node2, NULL);
        EXPECT_HR(hr, E_INVALIDARG);
        /* NOTE: Need to test that arg2 gets cleared on Error. */

        hr = IXMLDOMNode_get_prefix(node2, &str);
        EXPECT_HR(hr, S_OK);
        ok( !lstrcmpW( str, _bstr_("Model")), "got %s\n", wine_dbgstr_w(str));
        SysFreeString(str);

        hr = IXMLDOMNode_get_nodeName(node2, &str);
        EXPECT_HR(hr, S_OK);
        ok(!lstrcmpW( str, _bstr_("Model:Package")), "got %s\n", wine_dbgstr_w(str));
        SysFreeString(str);

        /* Test get_namespaceURI */
        hr = IXMLDOMNode_get_namespaceURI(node2, NULL);
        EXPECT_HR(hr, E_INVALIDARG);
        /* NOTE: Need to test that arg2 gets cleared on Error. */

        hr = IXMLDOMNode_get_namespaceURI(node2, &str);
        EXPECT_HR(hr, S_OK);
        ok(!lstrcmpW( str, _bstr_("http://omg.org/mof.Model/1.3")), "got %s\n", wine_dbgstr_w(str));
        SysFreeString(str);

        hr = IXMLDOMNode_QueryInterface(node2, &IID_IXMLDOMElement, (void**)&elem);
        EXPECT_HR(hr, S_OK);

        hr = IXMLDOMElement_getAttributeNode(elem, _bstr_("Model:name2"), &attr);
        EXPECT_HR(hr, S_OK);

        hr = IXMLDOMAttribute_get_nodeName(attr, &str);
        EXPECT_HR(hr, S_OK);
        ok(!lstrcmpW( str, _bstr_("Model:name2")), "got %s\n", wine_dbgstr_w(str));
        SysFreeString(str);

        hr = IXMLDOMAttribute_get_prefix(attr, &str);
        EXPECT_HR(hr, S_OK);
        ok(!lstrcmpW( str, _bstr_("Model")), "got %s\n", wine_dbgstr_w(str));
        SysFreeString(str);

        IXMLDOMAttribute_Release(attr);
        IXMLDOMElement_Release(elem);

        IXMLDOMNode_Release(node2);
        IXMLDOMNode_Release(node);
    }

    IXMLDOMDocument_Release(doc);

    free_bstrs();
}