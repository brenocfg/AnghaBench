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
struct msxmlsupported_data_t {scalar_t__ clsid; int /*<<< orphan*/  name; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ISAXAttributes ;
typedef  int /*<<< orphan*/  IMXAttributes ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_SAXAttributes ; 
 int /*<<< orphan*/  CLSID_SAXAttributes30 ; 
 int /*<<< orphan*/  CoCreateInstance (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  IID_IMXAttributes ; 
 int /*<<< orphan*/  IID_ISAXAttributes ; 
 int /*<<< orphan*/  IMXAttributes_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMXAttributes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMXAttributes_addAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISAXAttributes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISAXAttributes_getIndexFromName (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ IsEqualGUID (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  is_clsid_supported (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrlenW (char const*) ; 
 int /*<<< orphan*/  mxattributes_support_data ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int) ; 
 struct msxmlsupported_data_t* saxattr_support_data ; 

__attribute__((used)) static void test_mxattr_localname(void)
{
    static const WCHAR localname1W[] = {'l','o','c','a','l','n','a','m','e','1',0};
    static const WCHAR localnameW[] = {'l','o','c','a','l','n','a','m','e',0};
    static const WCHAR uri1W[] = {'u','r','i','1',0};
    static const WCHAR uriW[] = {'u','r','i',0};

    const struct msxmlsupported_data_t *table = saxattr_support_data;

    while (table->clsid)
    {
        ISAXAttributes *saxattr;
        IMXAttributes *mxattr;
        HRESULT hr;
        int index;

        if (!is_clsid_supported(table->clsid, mxattributes_support_data))
        {
            table++;
            continue;
        }

        hr = CoCreateInstance(table->clsid, NULL, CLSCTX_INPROC_SERVER,
            &IID_IMXAttributes, (void**)&mxattr);
        EXPECT_HR(hr, S_OK);

        hr = IMXAttributes_QueryInterface(mxattr, &IID_ISAXAttributes, (void**)&saxattr);
        EXPECT_HR(hr, S_OK);

        hr = ISAXAttributes_getIndexFromName(saxattr, NULL, 0, NULL, 0, &index);
        EXPECT_HR(hr, E_INVALIDARG);

        /* add some ambiguos attribute names */
        hr = IMXAttributes_addAttribute(mxattr, _bstr_("uri"), _bstr_("localname"),
            _bstr_("a:localname"), _bstr_(""), _bstr_("value"));
        EXPECT_HR(hr, S_OK);
        hr = IMXAttributes_addAttribute(mxattr, _bstr_("uri"), _bstr_("localname"),
            _bstr_("b:localname"), _bstr_(""), _bstr_("value"));
        EXPECT_HR(hr, S_OK);

        index = -1;
        hr = ISAXAttributes_getIndexFromName(saxattr, uriW, lstrlenW(uriW), localnameW, lstrlenW(localnameW), &index);
        EXPECT_HR(hr, S_OK);
        ok(index == 0, "%s: got index %d\n", table->name, index);

        index = -1;
        hr = ISAXAttributes_getIndexFromName(saxattr, uri1W, lstrlenW(uri1W), localnameW, lstrlenW(localnameW), &index);
        EXPECT_HR(hr, E_INVALIDARG);
        ok(index == -1, "%s: got index %d\n", table->name, index);

        index = -1;
        hr = ISAXAttributes_getIndexFromName(saxattr, uriW, lstrlenW(uriW), localname1W, lstrlenW(localname1W), &index);
        EXPECT_HR(hr, E_INVALIDARG);
        ok(index == -1, "%s: got index %d\n", table->name, index);

        if (IsEqualGUID(table->clsid, &CLSID_SAXAttributes) ||
            IsEqualGUID(table->clsid, &CLSID_SAXAttributes30))
        {
            hr = ISAXAttributes_getIndexFromName(saxattr, NULL, 0, NULL, 0, NULL);
            EXPECT_HR(hr, E_POINTER);

            hr = ISAXAttributes_getIndexFromName(saxattr, uriW, lstrlenW(uriW), localname1W, lstrlenW(localname1W), NULL);
            EXPECT_HR(hr, E_POINTER);
        }
        else
        {
            hr = ISAXAttributes_getIndexFromName(saxattr, NULL, 0, NULL, 0, NULL);
            EXPECT_HR(hr, E_INVALIDARG);

            hr = ISAXAttributes_getIndexFromName(saxattr, uriW, lstrlenW(uriW), localname1W, lstrlenW(localname1W), NULL);
            EXPECT_HR(hr, E_INVALIDARG);
        }

        hr = ISAXAttributes_getIndexFromName(saxattr, uriW, lstrlenW(uriW), NULL, 0, &index);
        EXPECT_HR(hr, E_INVALIDARG);

        hr = ISAXAttributes_getIndexFromName(saxattr, NULL, 0, localname1W, lstrlenW(localname1W), &index);
        EXPECT_HR(hr, E_INVALIDARG);

        table++;

        ISAXAttributes_Release(saxattr);
        IMXAttributes_Release(mxattr);
        free_bstrs();
    }
}