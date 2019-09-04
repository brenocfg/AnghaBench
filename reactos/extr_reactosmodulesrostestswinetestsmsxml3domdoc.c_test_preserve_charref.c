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
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMElement ;
typedef  int /*<<< orphan*/  IXMLDOMDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IXMLDOMDocument2_get_documentElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMDocument2_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ IXMLDOMDocument2_put_preserveWhiteSpace (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMElement_get_childNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/  _bstr_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  charrefsxml ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_preserve_charref(IXMLDOMDocument2 *doc, VARIANT_BOOL preserve)
{
    static const WCHAR b1_p[] = {' ','T','e','x','t',' ','A',' ','e','n','d',' ',0};
    static const WCHAR b1_i[] = {'T','e','x','t',' ','A',' ','e','n','d',0};
    static const WCHAR b2_p[] = {'A','B',' ','C',' ',0};
    static const WCHAR b2_i[] = {'A','B',' ','C',0};
    IXMLDOMNodeList *list;
    IXMLDOMElement *root;
    IXMLDOMNode *node;
    const WCHAR *text;
    VARIANT_BOOL b;
    HRESULT hr;
    BSTR s;

    hr = IXMLDOMDocument2_put_preserveWhiteSpace(doc, preserve);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXMLDOMDocument2_loadXML(doc, _bstr_(charrefsxml), &b);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXMLDOMDocument2_get_documentElement(doc, &root);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXMLDOMElement_get_childNodes(root, &list);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    IXMLDOMElement_Release(root);

    text = preserve == VARIANT_TRUE ? b1_p : b1_i;
    hr = IXMLDOMNodeList_get_item(list, 0, &node);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = IXMLDOMNode_get_text(node, &s);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!lstrcmpW(s, text), "0x%x, got %s\n", preserve, wine_dbgstr_w(s));
    SysFreeString(s);
    IXMLDOMNode_Release(node);

    text = preserve == VARIANT_TRUE ? b2_p : b2_i;
    hr = IXMLDOMNodeList_get_item(list, 1, &node);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = IXMLDOMNode_get_text(node, &s);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!lstrcmpW(s, text), "0x%x, got %s\n", preserve, wine_dbgstr_w(s));
    SysFreeString(s);
    IXMLDOMNode_Release(node);

    IXMLDOMNodeList_Release(list);
}