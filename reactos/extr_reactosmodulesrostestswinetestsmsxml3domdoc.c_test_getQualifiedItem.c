#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; char* uri; int /*<<< orphan*/  hr; } ;
typedef  TYPE_1__ ns_item_t ;
typedef  scalar_t__ VARIANT_BOOL ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  void IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMNamedNodeMap ;
typedef  int /*<<< orphan*/  IXMLDOMElement ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IID_IXMLDOMElement ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMDocument_get_documentElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IXMLDOMDocument_selectSingleNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMElement_get_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMElement_get_childNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNamedNodeMap_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNamedNodeMap_getNamedItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMNamedNodeMap_getQualifiedItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMNamedNodeMap_get_length (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  IXMLDOMNode_QueryInterface (void*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (void*) ; 
 int /*<<< orphan*/  IXMLDOMNode_get_attributes (void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/ * _bstr_ (char*) ; 
 char* complete4A ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 char* default_ns_doc ; 
 int /*<<< orphan*/  free_bstrs () ; 
 TYPE_1__* named_item_tests ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 TYPE_1__* qualified_item_tests ; 

__attribute__((used)) static void test_getQualifiedItem(void)
{
    IXMLDOMNode *pr_node, *node;
    IXMLDOMNodeList *root_list;
    IXMLDOMNamedNodeMap *map;
    IXMLDOMElement *element;
    const ns_item_t* ptr;
    IXMLDOMDocument *doc;
    VARIANT_BOOL b;
    HRESULT hr;
    LONG len;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_loadXML( doc, _bstr_(complete4A), &b );
    EXPECT_HR(hr, S_OK);
    ok( b == VARIANT_TRUE, "failed to load XML string\n");

    hr = IXMLDOMDocument_get_documentElement(doc, &element);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMElement_get_childNodes(element, &root_list);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMNodeList_get_item(root_list, 1, &pr_node);
    EXPECT_HR(hr, S_OK);
    IXMLDOMNodeList_Release(root_list);

    hr = IXMLDOMNode_get_attributes(pr_node, &map);
    EXPECT_HR(hr, S_OK);
    IXMLDOMNode_Release(pr_node);

    len = 0;
    hr = IXMLDOMNamedNodeMap_get_length(map, &len);
    EXPECT_HR(hr, S_OK);
    ok( len == 3, "length %d\n", len);

    hr = IXMLDOMNamedNodeMap_getQualifiedItem(map, NULL, NULL, NULL);
    EXPECT_HR(hr, E_INVALIDARG);

    node = (void*)0xdeadbeef;
    hr = IXMLDOMNamedNodeMap_getQualifiedItem(map, NULL, NULL, &node);
    EXPECT_HR(hr, E_INVALIDARG);
    ok( node == (void*)0xdeadbeef, "got %p\n", node);

    hr = IXMLDOMNamedNodeMap_getQualifiedItem(map, _bstr_("id"), NULL, NULL);
    EXPECT_HR(hr, E_INVALIDARG);

    hr = IXMLDOMNamedNodeMap_getQualifiedItem(map, _bstr_("id"), NULL, &node);
    EXPECT_HR(hr, S_OK);

    IXMLDOMNode_Release(node);
    IXMLDOMNamedNodeMap_Release(map);
    IXMLDOMElement_Release(element);

    hr = IXMLDOMDocument_loadXML(doc, _bstr_(default_ns_doc), &b);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMDocument_selectSingleNode(doc, _bstr_("a"), &node);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMNode_QueryInterface(node, &IID_IXMLDOMElement, (void**)&element);
    EXPECT_HR(hr, S_OK);
    IXMLDOMNode_Release(node);

    hr = IXMLDOMElement_get_attributes(element, &map);
    EXPECT_HR(hr, S_OK);

    ptr = qualified_item_tests;
    while (ptr->name)
    {
       node = (void*)0xdeadbeef;
       hr = IXMLDOMNamedNodeMap_getQualifiedItem(map, _bstr_(ptr->name), _bstr_(ptr->uri), &node);
       ok(hr == ptr->hr, "%s, %s: got 0x%08x, expected 0x%08x\n", ptr->name, ptr->uri, hr, ptr->hr);
       if (hr == S_OK)
           IXMLDOMNode_Release(node);
       else
           ok(node == NULL, "%s, %s: got %p\n", ptr->name, ptr->uri, node);
       ptr++;
    }

    ptr = named_item_tests;
    while (ptr->name)
    {
       node = (void*)0xdeadbeef;
       hr = IXMLDOMNamedNodeMap_getNamedItem(map, _bstr_(ptr->name), &node);
       ok(hr == ptr->hr, "%s: got 0x%08x, expected 0x%08x\n", ptr->name, hr, ptr->hr);
       if (hr == S_OK)
           IXMLDOMNode_Release(node);
       else
           ok(node == NULL, "%s: got %p\n", ptr->name, node);
       ptr++;
    }

    IXMLDOMNamedNodeMap_Release(map);

    IXMLDOMElement_Release(element);
    IXMLDOMDocument_Release(doc);
    free_bstrs();
}