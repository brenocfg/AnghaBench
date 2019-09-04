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
typedef  int /*<<< orphan*/  IVBSAXAttributes ;
typedef  int /*<<< orphan*/  ISAXAttributes ;
typedef  int /*<<< orphan*/  IMXAttributes ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_SAXAttributes ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT_REF (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IID_IMXAttributes ; 
 int /*<<< orphan*/  IID_ISAXAttributes ; 
 int /*<<< orphan*/  IID_IVBSAXAttributes ; 
 int /*<<< orphan*/  IMXAttributes_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMXAttributes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISAXAttributes_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ISAXAttributes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IVBSAXAttributes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static void test_mxattr_qi(void)
{
    IVBSAXAttributes *vbsaxattr, *vbsaxattr2;
    ISAXAttributes *saxattr;
    IMXAttributes *mxattr;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_SAXAttributes, NULL, CLSCTX_INPROC_SERVER,
            &IID_IMXAttributes, (void**)&mxattr);
    EXPECT_HR(hr, S_OK);

    EXPECT_REF(mxattr, 1);
    hr = IMXAttributes_QueryInterface(mxattr, &IID_ISAXAttributes, (void**)&saxattr);
    EXPECT_HR(hr, S_OK);

    EXPECT_REF(mxattr, 2);
    EXPECT_REF(saxattr, 2);

    hr = IMXAttributes_QueryInterface(mxattr, &IID_IVBSAXAttributes, (void**)&vbsaxattr);
    EXPECT_HR(hr, S_OK);

    EXPECT_REF(vbsaxattr, 3);
    EXPECT_REF(mxattr, 3);
    EXPECT_REF(saxattr, 3);

    hr = ISAXAttributes_QueryInterface(saxattr, &IID_IVBSAXAttributes, (void**)&vbsaxattr2);
    EXPECT_HR(hr, S_OK);

    EXPECT_REF(vbsaxattr, 4);
    EXPECT_REF(mxattr, 4);
    EXPECT_REF(saxattr, 4);

    IMXAttributes_Release(mxattr);
    ISAXAttributes_Release(saxattr);
    IVBSAXAttributes_Release(vbsaxattr);
    IVBSAXAttributes_Release(vbsaxattr2);
}