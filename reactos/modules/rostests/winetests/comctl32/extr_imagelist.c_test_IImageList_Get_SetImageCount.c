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
typedef  int INT ;
typedef  int /*<<< orphan*/  IImageList ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HIMAGELIST ;

/* Variables and functions */
 scalar_t__ IImageList_GetImageCount (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IImageList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IImageList_SetImageCount (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ILC_COLOR16 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pImageList_Create (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_IImageList_Get_SetImageCount(void)
{
    IImageList *imgl;
    HIMAGELIST himl;
    HRESULT hr;
    INT ret;

    /* create an imagelist to play with */
    himl = pImageList_Create(84, 84, ILC_COLOR16, 0, 3);
    ok(himl != 0,"failed to create imagelist\n");

    imgl = (IImageList *) himl;

    /* check SetImageCount/GetImageCount */
    hr = IImageList_SetImageCount(imgl, 3);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ret = 0;
    hr = IImageList_GetImageCount(imgl, &ret);
    ok(hr == S_OK && ret == 3, "invalid image count after increase\n");
    hr = IImageList_SetImageCount(imgl, 1);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ret = 0;
    hr = IImageList_GetImageCount(imgl, &ret);
    ok(hr == S_OK && ret == 1, "invalid image count after decrease to 1\n");
    hr = IImageList_SetImageCount(imgl, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ret = -1;
    hr = IImageList_GetImageCount(imgl, &ret);
    ok(hr == S_OK && ret == 0, "invalid image count after decrease to 0\n");

    IImageList_Release(imgl);
}