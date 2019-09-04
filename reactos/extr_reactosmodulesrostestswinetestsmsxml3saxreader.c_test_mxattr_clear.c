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
typedef  void WCHAR ;
typedef  int /*<<< orphan*/  ISAXAttributes ;
typedef  int /*<<< orphan*/  IMXAttributes ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_SAXAttributes ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  IID_IMXAttributes ; 
 int /*<<< orphan*/  IID_ISAXAttributes ; 
 int /*<<< orphan*/  IMXAttributes_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMXAttributes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMXAttributes_addAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMXAttributes_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISAXAttributes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISAXAttributes_getLength (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ISAXAttributes_getQName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const**,int*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  lstrcmpW (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,void const*) ; 
 void const* wine_dbgstr_w (void const*) ; 

__attribute__((used)) static void test_mxattr_clear(void)
{
    ISAXAttributes *saxattr;
    IMXAttributes *mxattr;
    const WCHAR *ptr;
    HRESULT hr;
    int len;

    hr = CoCreateInstance(&CLSID_SAXAttributes, NULL, CLSCTX_INPROC_SERVER,
        &IID_IMXAttributes, (void**)&mxattr);
    EXPECT_HR(hr, S_OK);

    hr = IMXAttributes_QueryInterface(mxattr, &IID_ISAXAttributes, (void**)&saxattr);
    EXPECT_HR(hr, S_OK);

    hr = ISAXAttributes_getQName(saxattr, 0, NULL, NULL);
    EXPECT_HR(hr, E_INVALIDARG);

    hr = ISAXAttributes_getQName(saxattr, 0, &ptr, &len);
    EXPECT_HR(hr, E_INVALIDARG);

    hr = IMXAttributes_clear(mxattr);
    EXPECT_HR(hr, S_OK);

    hr = IMXAttributes_addAttribute(mxattr, _bstr_("uri"), _bstr_("local"),
        _bstr_("qname"), _bstr_("type"), _bstr_("value"));
    EXPECT_HR(hr, S_OK);

    len = -1;
    hr = ISAXAttributes_getLength(saxattr, &len);
    EXPECT_HR(hr, S_OK);
    ok(len == 1, "got %d\n", len);

    len = -1;
    hr = ISAXAttributes_getQName(saxattr, 0, NULL, &len);
    EXPECT_HR(hr, E_POINTER);
    ok(len == -1, "got %d\n", len);

    ptr = (void*)0xdeadbeef;
    hr = ISAXAttributes_getQName(saxattr, 0, &ptr, NULL);
    EXPECT_HR(hr, E_POINTER);
    ok(ptr == (void*)0xdeadbeef, "got %p\n", ptr);

    len = 0;
    hr = ISAXAttributes_getQName(saxattr, 0, &ptr, &len);
    EXPECT_HR(hr, S_OK);
    ok(len == 5, "got %d\n", len);
    ok(!lstrcmpW(ptr, _bstr_("qname")), "got %s\n", wine_dbgstr_w(ptr));

    hr = IMXAttributes_clear(mxattr);
    EXPECT_HR(hr, S_OK);

    len = -1;
    hr = ISAXAttributes_getLength(saxattr, &len);
    EXPECT_HR(hr, S_OK);
    ok(len == 0, "got %d\n", len);

    len = -1;
    ptr = (void*)0xdeadbeef;
    hr = ISAXAttributes_getQName(saxattr, 0, &ptr, &len);
    EXPECT_HR(hr, E_INVALIDARG);
    ok(len == -1, "got %d\n", len);
    ok(ptr == (void*)0xdeadbeef, "got %p\n", ptr);

    IMXAttributes_Release(mxattr);
    ISAXAttributes_Release(saxattr);
    free_bstrs();
}