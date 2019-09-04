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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IXMLDOMSchemaCollection ;
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMElement ;
typedef  int /*<<< orphan*/  IXMLDOMDocument2 ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  IXMLDOMAttribute ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_DOMDocument2 ; 
 int /*<<< orphan*/  CLSID_XMLSchemaCache ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument2 ; 
 int /*<<< orphan*/  IID_IXMLDOMElement ; 
 int /*<<< orphan*/  IID_IXMLDOMSchemaCollection ; 
 int /*<<< orphan*/  IXMLDOMAttribute_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMAttribute_get_ownerDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMDocument2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMDocument2_get_firstChild (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMDocument2_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IXMLDOMDocument_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMDocument_get_documentElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMElement_getAttributeNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMElement_get_childNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_get_length (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IXMLDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNode_get_ownerDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMSchemaCollection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bstr_ (char const*) ; 
 int /*<<< orphan*/  check_default_props (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_set_props (int /*<<< orphan*/ *) ; 
 char* complete4A ; 
 int /*<<< orphan*/ * create_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  is_clsid_supported (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ole_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unset_props (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_get_ownerDocument(void)
{
    IXMLDOMDocument *doc1, *doc2, *doc3;
    IXMLDOMDocument2 *doc, *doc_owner;
    IXMLDOMNode *node;
    IXMLDOMSchemaCollection *cache;
    VARIANT_BOOL b;
    VARIANT var;
    IXMLDOMElement *element;
    IXMLDOMNodeList *node_list;
    IXMLDOMAttribute *attr;
    LONG i, len;
    HRESULT hr;
    const CHAR nodeXML[] =
    "<root id='0'>"
    "   <!-- comment node 0 -->"
    "   text node 0"
    "   <x attr='val'></x>"
    "   <?foo value='PI for x'?>"
    "   <![CDATA[ cdata ]]>"
    "</root>";

    if (!is_clsid_supported(&CLSID_DOMDocument2, &IID_IXMLDOMDocument2)) return;
    if (!is_clsid_supported(&CLSID_XMLSchemaCache, &IID_IXMLDOMSchemaCollection)) return;

    doc = create_document(&IID_IXMLDOMDocument2);
    cache = create_cache(&IID_IXMLDOMSchemaCollection);

    VariantInit(&var);

    ole_check(IXMLDOMDocument2_loadXML(doc, _bstr_(complete4A), &b));
    ok(b == VARIANT_TRUE, "failed to load XML string\n");

    check_default_props(doc);

    /* set properties and check that new instances use them */
    set_props(doc, cache);
    check_set_props(doc);

    ole_check(IXMLDOMDocument2_get_firstChild(doc, &node));
    ole_check(IXMLDOMNode_get_ownerDocument(node, &doc1));

    /* new interface keeps props */
    ole_check(IXMLDOMDocument_QueryInterface(doc1, &IID_IXMLDOMDocument2, (void**)&doc_owner));
    ok( doc_owner != doc, "got %p, doc %p\n", doc_owner, doc);
    check_set_props(doc_owner);
    IXMLDOMDocument2_Release(doc_owner);

    ole_check(IXMLDOMNode_get_ownerDocument(node, &doc2));
    IXMLDOMNode_Release(node);

    ok(doc1 != doc2, "got %p, expected %p. original %p\n", doc2, doc1, doc);

    /* reload */
    ole_check(IXMLDOMDocument2_loadXML(doc, _bstr_(complete4A), &b));
    ok(b == VARIANT_TRUE, "failed to load XML string\n");

    /* properties retained even after reload */
    check_set_props(doc);

    ole_check(IXMLDOMDocument2_get_firstChild(doc, &node));
    ole_check(IXMLDOMNode_get_ownerDocument(node, &doc3));
    IXMLDOMNode_Release(node);

    ole_check(IXMLDOMDocument_QueryInterface(doc3, &IID_IXMLDOMDocument2, (void**)&doc_owner));
    ok(doc3 != doc1 && doc3 != doc2 && doc_owner != doc, "got %p, (%p, %p, %p)\n", doc3, doc, doc1, doc2);
    check_set_props(doc_owner);

    /* changing properties for one instance changes them for all */
    unset_props(doc_owner);
    check_default_props(doc_owner);
    check_default_props(doc);

    /* NULL check */
    hr = IXMLDOMDocument_loadXML(doc1, _bstr_(nodeXML), &b);
    EXPECT_HR(hr, S_OK);
    ok(b == VARIANT_TRUE, "failed to load XML string\n");

    hr = IXMLDOMDocument_get_documentElement(doc1, &element);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMElement_get_childNodes(element, &node_list);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMNodeList_get_length(node_list, &len);
    EXPECT_HR(hr, S_OK);

    for(i = 0; i < len; i++) {
        hr = IXMLDOMNodeList_get_item(node_list, i, &node);
        EXPECT_HR(hr, S_OK);

        hr = IXMLDOMNode_get_ownerDocument(node, NULL);
        EXPECT_HR(hr, E_INVALIDARG);

        IXMLDOMNode_Release(node);
    }
    IXMLDOMElement_Release(element);

    /* Test Attribute Node */
    hr = IXMLDOMNodeList_get_item(node_list, 2, &node);
    EXPECT_HR(hr, S_OK);
    hr = IXMLDOMNode_QueryInterface(node, &IID_IXMLDOMElement, (void**)&element);
    EXPECT_HR(hr, S_OK);
    IXMLDOMNode_Release(node);

    hr = IXMLDOMElement_getAttributeNode(element, _bstr_("attr"), &attr);
    EXPECT_HR(hr, S_OK);
    ok(attr != NULL, "attr == NULL\n");
    IXMLDOMElement_Release(element);
    hr = IXMLDOMAttribute_get_ownerDocument(attr, NULL);
    EXPECT_HR(hr, E_INVALIDARG);
    IXMLDOMAttribute_Release(attr);
    IXMLDOMNodeList_Release(node_list);

    IXMLDOMSchemaCollection_Release(cache);
    IXMLDOMDocument_Release(doc1);
    IXMLDOMDocument_Release(doc2);
    IXMLDOMDocument_Release(doc3);
    IXMLDOMDocument2_Release(doc);
    IXMLDOMDocument2_Release(doc_owner);
    free_bstrs();
}