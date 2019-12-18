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
typedef  int /*<<< orphan*/  IImageList ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HIMAGELIST ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ IImageList_GetIconSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IImageList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ILC_COLOR16 ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pImageList_Create (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_IImageList_GetIconSize(void)
{
    IImageList *imgl;
    HIMAGELIST himl;
    int cx, cy;
    HRESULT hr;

    himl = pImageList_Create(16, 16, ILC_COLOR16, 0, 3);
    imgl = (IImageList*)himl;

    hr = IImageList_GetIconSize(imgl, NULL, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = IImageList_GetIconSize(imgl, &cx, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = IImageList_GetIconSize(imgl, NULL, &cy);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    IImageList_Release(imgl);
}