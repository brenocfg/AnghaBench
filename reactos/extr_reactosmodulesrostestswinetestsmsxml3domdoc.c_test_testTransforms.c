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
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IID_IXMLDOMNode ; 
 scalar_t__ IXMLDOMDocument_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_transformNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bstr_ (int /*<<< orphan*/ ) ; 
 int compareIgnoreReturns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  szTransformOutput ; 
 int /*<<< orphan*/  szTransformSSXML ; 
 int /*<<< orphan*/  szTransformXML ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_testTransforms(void)
{
    IXMLDOMDocument *doc, *docSS;
    IXMLDOMNode *pNode;
    VARIANT_BOOL bSucc;
    HRESULT hr;

    doc = create_document(&IID_IXMLDOMDocument);
    docSS = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_loadXML(doc, _bstr_(szTransformXML), &bSucc);
    ok(hr == S_OK, "ret %08x\n", hr );

    hr = IXMLDOMDocument_loadXML(docSS, _bstr_(szTransformSSXML), &bSucc);
    ok(hr == S_OK, "ret %08x\n", hr );

    hr = IXMLDOMDocument_QueryInterface(docSS, &IID_IXMLDOMNode, (void**)&pNode );
    ok(hr == S_OK, "ret %08x\n", hr );
    if(hr == S_OK)
    {
        BSTR bOut;

        hr = IXMLDOMDocument_transformNode(doc, pNode, &bOut);
        ok(hr == S_OK, "ret %08x\n", hr );
        if(hr == S_OK)
        {
            ok( compareIgnoreReturns( bOut, _bstr_(szTransformOutput)), "got output %s\n", wine_dbgstr_w(bOut));
            SysFreeString(bOut);
        }

        IXMLDOMNode_Release(pNode);
    }

    IXMLDOMDocument_Release(docSS);
    IXMLDOMDocument_Release(doc);

    free_bstrs();
}