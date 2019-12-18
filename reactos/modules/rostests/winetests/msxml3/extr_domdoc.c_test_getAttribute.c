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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IXMLDOMElement ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMDocument_get_documentElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMElement_getAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ VT_BSTR ; 
 scalar_t__ VT_NULL ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 char* szExampleXML ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_getAttribute(void)
{
    IXMLDOMDocument *doc;
    IXMLDOMElement *elem;
    VARIANT_BOOL v;
    VARIANT var;
    HRESULT hr;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_loadXML(doc, _bstr_(szExampleXML), &v);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMDocument_get_documentElement(doc, &elem);
    EXPECT_HR(hr, S_OK);

    VariantInit(&var);
    hr = IXMLDOMElement_getAttribute( elem, _bstr_("xmlns:foo"), &var );
    EXPECT_HR(hr, S_OK);
    ok( V_VT(&var) == VT_BSTR, "vt = %x\n", V_VT(&var));
    ok( !lstrcmpW(V_BSTR(&var), _bstr_("urn:uuid:86B2F87F-ACB6-45cd-8B77-9BDB92A01A29")), "wrong attr value: %s\n", wine_dbgstr_w(V_BSTR(&var)));
    VariantClear(&var);

    hr = IXMLDOMElement_getAttribute( elem, _bstr_("a"), &var );
    EXPECT_HR(hr, S_OK);
    ok( V_VT(&var) == VT_BSTR, "vt = %x\n", V_VT(&var));
    ok( !lstrcmpW(V_BSTR(&var), _bstr_("attr a")), "wrong attr value: %s\n", wine_dbgstr_w(V_BSTR(&var)));
    VariantClear(&var);

    hr = IXMLDOMElement_getAttribute( elem, _bstr_("foo:b"), &var );
    EXPECT_HR(hr, S_OK);
    ok( V_VT(&var) == VT_BSTR, "vt = %x\n", V_VT(&var));
    ok( !lstrcmpW(V_BSTR(&var), _bstr_("attr b")), "wrong attr value: %s\n", wine_dbgstr_w(V_BSTR(&var)));
    VariantClear(&var);

    hr = IXMLDOMElement_getAttribute( elem, _bstr_("b"), &var );
    EXPECT_HR(hr, S_FALSE);
    ok( V_VT(&var) == VT_NULL, "vt = %x\n", V_VT(&var));
    VariantClear(&var);

    hr = IXMLDOMElement_getAttribute( elem, _bstr_("non-existent"), &var );
    EXPECT_HR(hr, S_FALSE);
    ok( V_VT(&var) == VT_NULL, "vt = %x\n", V_VT(&var));
    VariantClear(&var);

    IXMLDOMElement_Release(elem);
    IXMLDOMDocument_Release(doc);
    free_bstrs();
}