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
struct whitespace_t {int /*<<< orphan*/  name; scalar_t__ clsid; } ;
typedef  scalar_t__ VARIANT_BOOL ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMElement ;
typedef  int /*<<< orphan*/  IXMLDOMDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 scalar_t__ CoCreateInstance (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument2 ; 
 scalar_t__ IXMLDOMDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMDocument2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument2_get_documentElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMDocument2_get_preserveWhiteSpace (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IXMLDOMDocument2_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ IXMLDOMDocument2_put_preserveWhiteSpace (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ IXMLDOMDocument2_setProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXMLDOMElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMElement_get_childNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNodeList_get_length (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ VARIANT_FALSE ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int /*<<< orphan*/  _variantbstr_ (char*) ; 
 int /*<<< orphan*/  check_ws_ignored (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  check_ws_preserved (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 char* complete7 ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  is_clsid_supported (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ole_check (scalar_t__) ; 
 char* szExampleXML ; 
 int /*<<< orphan*/  test_preserve_charref (int /*<<< orphan*/ *,scalar_t__) ; 
 struct whitespace_t* whitespace_test_data ; 

__attribute__((used)) static void test_whitespace(void)
{
    const struct whitespace_t *class_ptr = whitespace_test_data;

    while (class_ptr->clsid)
    {
        IXMLDOMDocument2 *doc1, *doc2, *doc3, *doc4;
        IXMLDOMNodeList *list;
        IXMLDOMElement *root;
        VARIANT_BOOL b;
        HRESULT hr;
        LONG len;

        if (!is_clsid_supported(class_ptr->clsid, &IID_IXMLDOMDocument2))
        {
            class_ptr++;
            continue;
        }

        hr = CoCreateInstance(class_ptr->clsid, NULL, CLSCTX_INPROC_SERVER,
                &IID_IXMLDOMDocument2, (void**)&doc1);
        ok(hr == S_OK, "got 0x%08x\n", hr);

        hr = CoCreateInstance(class_ptr->clsid, NULL, CLSCTX_INPROC_SERVER,
                &IID_IXMLDOMDocument2, (void**)&doc2);
        ok(hr == S_OK, "got 0x%08x\n", hr);

        ole_check(IXMLDOMDocument2_put_preserveWhiteSpace(doc2, VARIANT_TRUE));
        ole_check(IXMLDOMDocument2_get_preserveWhiteSpace(doc1, &b));
        ok(b == VARIANT_FALSE, "expected false\n");
        ole_check(IXMLDOMDocument2_get_preserveWhiteSpace(doc2, &b));
        ok(b == VARIANT_TRUE, "expected true\n");

        ole_check(IXMLDOMDocument2_loadXML(doc1, _bstr_(szExampleXML), &b));
        ok(b == VARIANT_TRUE, "failed to load XML string\n");
        ole_check(IXMLDOMDocument2_loadXML(doc2, _bstr_(szExampleXML), &b));
        ok(b == VARIANT_TRUE, "failed to load XML string\n");

        /* switch to XPath */
        ole_check(IXMLDOMDocument2_setProperty(doc1, _bstr_("SelectionLanguage"), _variantbstr_("XPath")));
        ole_check(IXMLDOMDocument2_setProperty(doc2, _bstr_("SelectionLanguage"), _variantbstr_("XPath")));

        check_ws_ignored(class_ptr->name, doc1, NULL);
        check_ws_preserved(class_ptr->name, doc2, NULL);

        /* new instances copy the property */
        ole_check(IXMLDOMDocument2_QueryInterface(doc1, &IID_IXMLDOMDocument2, (void**) &doc3));
        ole_check(IXMLDOMDocument2_QueryInterface(doc2, &IID_IXMLDOMDocument2, (void**) &doc4));

        ole_check(IXMLDOMDocument2_get_preserveWhiteSpace(doc3, &b));
        ok(b == VARIANT_FALSE, "expected false\n");
        ole_check(IXMLDOMDocument2_get_preserveWhiteSpace(doc4, &b));
        ok(b == VARIANT_TRUE, "expected true\n");

        check_ws_ignored(class_ptr->name, doc3, NULL);
        check_ws_preserved(class_ptr->name, doc4, NULL);

        /* setting after loading xml affects trimming of leading/trailing ws only */
        ole_check(IXMLDOMDocument2_put_preserveWhiteSpace(doc1, VARIANT_TRUE));
        ole_check(IXMLDOMDocument2_put_preserveWhiteSpace(doc2, VARIANT_FALSE));

        /* the trailing "\n            " isn't there, because it was ws-only node */
        check_ws_ignored(class_ptr->name, doc1, " This is a description. ");
        check_ws_preserved(class_ptr->name, doc2, " This is a description.");

        /* it takes effect on reload */
        ole_check(IXMLDOMDocument2_get_preserveWhiteSpace(doc1, &b));
        ok(b == VARIANT_TRUE, "expected true\n");
        ole_check(IXMLDOMDocument2_get_preserveWhiteSpace(doc2, &b));
        ok(b == VARIANT_FALSE, "expected false\n");

        ole_check(IXMLDOMDocument2_loadXML(doc1, _bstr_(szExampleXML), &b));
        ok(b == VARIANT_TRUE, "failed to load XML string\n");
        ole_check(IXMLDOMDocument2_loadXML(doc2, _bstr_(szExampleXML), &b));
        ok(b == VARIANT_TRUE, "failed to load XML string\n");

        check_ws_preserved(class_ptr->name, doc1, NULL);
        check_ws_ignored(class_ptr->name, doc2, NULL);

        /* other instances follow suit */
        ole_check(IXMLDOMDocument2_get_preserveWhiteSpace(doc3, &b));
        ok(b == VARIANT_TRUE, "expected true\n");
        ole_check(IXMLDOMDocument2_get_preserveWhiteSpace(doc4, &b));
        ok(b == VARIANT_FALSE, "expected false\n");

        check_ws_preserved(class_ptr->name, doc3, NULL);
        check_ws_ignored(class_ptr->name, doc4, NULL);

        IXMLDOMDocument2_Release(doc2);
        IXMLDOMDocument2_Release(doc3);
        IXMLDOMDocument2_Release(doc4);

        /* text with char references */
        test_preserve_charref(doc1, VARIANT_TRUE);
        test_preserve_charref(doc1, VARIANT_FALSE);

        /* formatting whitespaces */
        hr = IXMLDOMDocument2_put_preserveWhiteSpace(doc1, VARIANT_FALSE);
        ok(hr == S_OK, "got 0x%08x\n", hr);

        hr = IXMLDOMDocument2_loadXML(doc1, _bstr_(complete7), &b);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        ok(b == VARIANT_TRUE, "for %x\n", b);

        hr = IXMLDOMDocument2_get_documentElement(doc1, &root);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        hr = IXMLDOMElement_get_childNodes(root, &list);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        len = 0;
        hr = IXMLDOMNodeList_get_length(list, &len);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        ok(len == 3, "got %d\n", len);
        IXMLDOMNodeList_Release(list);
        IXMLDOMElement_Release(root);

        IXMLDOMDocument2_Release(doc1);

        free_bstrs();

        class_ptr++;
    }
}