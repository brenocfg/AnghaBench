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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMXWriter ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_MXXMLWriter ; 
 int /*<<< orphan*/  CLSID_MXXMLWriter60 ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatchEx_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_IMXWriter ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IMXWriter_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMXWriter_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ is_clsid_supported (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxwriter_support_data ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_obj_dispex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_mxwriter_dispex(void)
{
    IDispatchEx *dispex;
    IMXWriter *writer;
    IUnknown *unk;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_MXXMLWriter, NULL, CLSCTX_INPROC_SERVER,
            &IID_IMXWriter, (void**)&writer);
    EXPECT_HR(hr, S_OK);

    hr = IMXWriter_QueryInterface(writer, &IID_IDispatchEx, (void**)&dispex);
    EXPECT_HR(hr, S_OK);
    hr = IDispatchEx_QueryInterface(dispex, &IID_IUnknown, (void**)&unk);
    test_obj_dispex(unk);
    IUnknown_Release(unk);
    IDispatchEx_Release(dispex);
    IMXWriter_Release(writer);

    if (is_clsid_supported(&CLSID_MXXMLWriter60, mxwriter_support_data))
    {
        hr = CoCreateInstance(&CLSID_MXXMLWriter60, NULL, CLSCTX_INPROC_SERVER, &IID_IUnknown, (void**)&unk);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        test_obj_dispex(unk);
        IUnknown_Release(unk);
    }
}