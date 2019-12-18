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
typedef  int /*<<< orphan*/  lcW ;
typedef  int /*<<< orphan*/  foW ;
typedef  char WCHAR ;
typedef  scalar_t__ VARIANT_BOOL ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_get_lastChild (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_lastChild (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNode_get_nodeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/  _bstr_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete4A ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_get_lastChild(void)
{
    static const WCHAR lcW[] = {'l','c',0};
    static const WCHAR foW[] = {'f','o',0};
    IXMLDOMDocument *doc;
    IXMLDOMNode *node, *child;
    VARIANT_BOOL b;
    HRESULT r;
    BSTR str;

    doc = create_document(&IID_IXMLDOMDocument);

    r = IXMLDOMDocument_loadXML( doc, _bstr_(complete4A), &b );
    ok( r == S_OK, "loadXML failed\n");
    ok( b == VARIANT_TRUE, "failed to load XML string\n");

    r = IXMLDOMDocument_get_lastChild( doc, &node );
    ok( r == S_OK, "ret %08x\n", r);

    r = IXMLDOMNode_get_nodeName( node, &str );
    ok( r == S_OK, "ret %08x\n", r);

    ok(memcmp(str, lcW, sizeof(lcW)) == 0, "expected \"lc\" node name\n");
    SysFreeString(str);

    r = IXMLDOMNode_get_lastChild( node, &child );
    ok( r == S_OK, "ret %08x\n", r);

    r = IXMLDOMNode_get_nodeName( child, &str );
    ok( r == S_OK, "ret %08x\n", r);

    ok(memcmp(str, foW, sizeof(foW)) == 0, "expected \"fo\" node name\n");
    SysFreeString(str);

    IXMLDOMNode_Release( child );
    IXMLDOMNode_Release( node );
    IXMLDOMDocument_Release( doc );

    free_bstrs();
}