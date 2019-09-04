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
typedef  int HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int IXMLDOMDocument_get_documentElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 int IXMLDOMElement_get_childNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNamedNodeMap_Release (int /*<<< orphan*/ *) ; 
 int IXMLDOMNamedNodeMap_get_length (int /*<<< orphan*/ *,int*) ; 
 int IXMLDOMNamedNodeMap_removeNamedItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IXMLDOMNamedNodeMap_setNamedItem (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 int IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (void*) ; 
 int IXMLDOMNode_get_attributes (void*,int /*<<< orphan*/ **) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/ * SysAllocString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/  _bstr_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete4A ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  szvr ; 

__attribute__((used)) static void test_removeNamedItem(void)
{
    IXMLDOMDocument *doc;
    IXMLDOMElement *element;
    IXMLDOMNode *pr_node, *removed_node, *removed_node2;
    IXMLDOMNodeList *root_list;
    IXMLDOMNamedNodeMap * pr_attrs;
    VARIANT_BOOL b;
    BSTR str;
    LONG len;
    HRESULT r;

    doc = create_document(&IID_IXMLDOMDocument);

    r = IXMLDOMDocument_loadXML( doc, _bstr_(complete4A), &b );
    ok( r == S_OK, "loadXML failed\n");
    ok( b == VARIANT_TRUE, "failed to load XML string\n");

    r = IXMLDOMDocument_get_documentElement( doc, &element );
    ok( r == S_OK, "ret %08x\n", r);

    r = IXMLDOMElement_get_childNodes( element, &root_list );
    ok( r == S_OK, "ret %08x\n", r);

    r = IXMLDOMNodeList_get_item( root_list, 1, &pr_node );
    ok( r == S_OK, "ret %08x\n", r);

    r = IXMLDOMNode_get_attributes( pr_node, &pr_attrs );
    ok( r == S_OK, "ret %08x\n", r);

    r = IXMLDOMNamedNodeMap_get_length( pr_attrs, &len );
    ok( r == S_OK, "ret %08x\n", r);
    ok( len == 3, "length %d\n", len);

    removed_node = (void*)0xdeadbeef;
    r = IXMLDOMNamedNodeMap_removeNamedItem( pr_attrs, NULL, &removed_node);
    ok ( r == E_INVALIDARG, "ret %08x\n", r);
    ok ( removed_node == (void*)0xdeadbeef, "got %p\n", removed_node);

    removed_node = (void*)0xdeadbeef;
    str = SysAllocString(szvr);
    r = IXMLDOMNamedNodeMap_removeNamedItem( pr_attrs, str, &removed_node);
    ok ( r == S_OK, "ret %08x\n", r);

    removed_node2 = (void*)0xdeadbeef;
    r = IXMLDOMNamedNodeMap_removeNamedItem( pr_attrs, str, &removed_node2);
    ok ( r == S_FALSE, "ret %08x\n", r);
    ok ( removed_node2 == NULL, "got %p\n", removed_node2 );

    r = IXMLDOMNamedNodeMap_get_length( pr_attrs, &len );
    ok( r == S_OK, "ret %08x\n", r);
    ok( len == 2, "length %d\n", len);

    r = IXMLDOMNamedNodeMap_setNamedItem( pr_attrs, removed_node, NULL);
    ok ( r == S_OK, "ret %08x\n", r);
    IXMLDOMNode_Release(removed_node);

    r = IXMLDOMNamedNodeMap_get_length( pr_attrs, &len );
    ok( r == S_OK, "ret %08x\n", r);
    ok( len == 3, "length %d\n", len);

    r = IXMLDOMNamedNodeMap_removeNamedItem( pr_attrs, str, NULL);
    ok ( r == S_OK, "ret %08x\n", r);

    r = IXMLDOMNamedNodeMap_get_length( pr_attrs, &len );
    ok( r == S_OK, "ret %08x\n", r);
    ok( len == 2, "length %d\n", len);

    r = IXMLDOMNamedNodeMap_removeNamedItem( pr_attrs, str, NULL);
    ok ( r == S_FALSE, "ret %08x\n", r);

    SysFreeString(str);

    IXMLDOMNamedNodeMap_Release( pr_attrs );
    IXMLDOMNode_Release( pr_node );
    IXMLDOMNodeList_Release( root_list );
    IXMLDOMElement_Release( element );
    IXMLDOMDocument_Release( doc );

    free_bstrs();
}