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
typedef  int LONG ;
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  void IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMNamedNodeMap ;
typedef  int /*<<< orphan*/  IXMLDOMElement ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  void* HRESULT ;

/* Variables and functions */
 void* E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 void* IXMLDOMDocument_get_documentElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 void* IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 void* IXMLDOMElement_get_childNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNamedNodeMap_Release (int /*<<< orphan*/ *) ; 
 void* IXMLDOMNamedNodeMap_get_length (int /*<<< orphan*/ *,int*) ; 
 void* IXMLDOMNamedNodeMap_removeQualifiedItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 void* IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (void*) ; 
 void* IXMLDOMNode_get_attributes (void*,int /*<<< orphan*/ **) ; 
 void* S_FALSE ; 
 void* S_OK ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/ * _bstr_ (char*) ; 
 char* complete4A ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_removeQualifiedItem(void)
{
    IXMLDOMDocument *doc;
    IXMLDOMElement *element;
    IXMLDOMNode *pr_node, *node;
    IXMLDOMNodeList *root_list;
    IXMLDOMNamedNodeMap *map;
    VARIANT_BOOL b;
    LONG len;
    HRESULT hr;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_loadXML( doc, _bstr_(complete4A), &b );
    ok( hr == S_OK, "loadXML failed\n");
    ok( b == VARIANT_TRUE, "failed to load XML string\n");

    hr = IXMLDOMDocument_get_documentElement(doc, &element);
    ok( hr == S_OK, "ret %08x\n", hr);

    hr = IXMLDOMElement_get_childNodes(element, &root_list);
    ok( hr == S_OK, "ret %08x\n", hr);

    hr = IXMLDOMNodeList_get_item(root_list, 1, &pr_node);
    ok( hr == S_OK, "ret %08x\n", hr);
    IXMLDOMNodeList_Release(root_list);

    hr = IXMLDOMNode_get_attributes(pr_node, &map);
    ok( hr == S_OK, "ret %08x\n", hr);
    IXMLDOMNode_Release(pr_node);

    hr = IXMLDOMNamedNodeMap_get_length(map, &len);
    ok( hr == S_OK, "ret %08x\n", hr);
    ok( len == 3, "length %d\n", len);

    hr = IXMLDOMNamedNodeMap_removeQualifiedItem(map, NULL, NULL, NULL);
    ok( hr == E_INVALIDARG, "ret %08x\n", hr);

    node = (void*)0xdeadbeef;
    hr = IXMLDOMNamedNodeMap_removeQualifiedItem(map, NULL, NULL, &node);
    ok( hr == E_INVALIDARG, "ret %08x\n", hr);
    ok( node == (void*)0xdeadbeef, "got %p\n", node);

    /* out pointer is optional */
    hr = IXMLDOMNamedNodeMap_removeQualifiedItem(map, _bstr_("id"), NULL, NULL);
    ok( hr == S_OK, "ret %08x\n", hr);

    /* already removed */
    hr = IXMLDOMNamedNodeMap_removeQualifiedItem(map, _bstr_("id"), NULL, NULL);
    ok( hr == S_FALSE, "ret %08x\n", hr);

    hr = IXMLDOMNamedNodeMap_removeQualifiedItem(map, _bstr_("vr"), NULL, &node);
    ok( hr == S_OK, "ret %08x\n", hr);
    IXMLDOMNode_Release(node);

    IXMLDOMNamedNodeMap_Release( map );
    IXMLDOMElement_Release( element );
    IXMLDOMDocument_Release( doc );
    free_bstrs();
}