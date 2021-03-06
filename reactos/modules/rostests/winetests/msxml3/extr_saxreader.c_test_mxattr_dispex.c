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
typedef  int /*<<< orphan*/  IMXAttributes ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_SAXAttributes ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatchEx_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_IMXAttributes ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IMXAttributes_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMXAttributes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  test_obj_dispex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_mxattr_dispex(void)
{
    IMXAttributes *mxattr;
    IDispatchEx *dispex;
    IUnknown *unk;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_SAXAttributes, NULL, CLSCTX_INPROC_SERVER,
            &IID_IMXAttributes, (void**)&mxattr);
    EXPECT_HR(hr, S_OK);

    hr = IMXAttributes_QueryInterface(mxattr, &IID_IDispatchEx, (void**)&dispex);
    EXPECT_HR(hr, S_OK);
    hr = IDispatchEx_QueryInterface(dispex, &IID_IUnknown, (void**)&unk);
    test_obj_dispex(unk);
    IUnknown_Release(unk);
    IDispatchEx_Release(dispex);

    IMXAttributes_Release(mxattr);
}