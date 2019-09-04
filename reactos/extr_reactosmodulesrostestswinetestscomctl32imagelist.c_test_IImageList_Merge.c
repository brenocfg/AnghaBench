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
typedef  int /*<<< orphan*/  IImageList ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/ * HICON ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateIcon (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IImageList ; 
 scalar_t__ IImageList_Merge (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IImageList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IImageList_ReplaceIcon (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  create_window () ; 
 int /*<<< orphan*/  hinst ; 
 int /*<<< orphan*/  icon_bits ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/ * pImageList_Create (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_IImageList_Merge(void)
{
    HIMAGELIST himl1, himl2;
    IImageList *imgl1, *imgl2, *merge;
    HICON hicon1;
    HWND hwnd = create_window();
    HRESULT hr;
    int ret;

    himl1 = pImageList_Create(32,32,0,0,3);
    ok(himl1 != NULL,"failed to create himl1\n");

    himl2 = pImageList_Create(32,32,0,0,3);
    ok(himl2 != NULL,"failed to create himl2\n");

    hicon1 = CreateIcon(hinst, 32, 32, 1, 1, icon_bits, icon_bits);
    ok(hicon1 != NULL, "failed to create hicon1\n");

    if (!himl1 || !himl2 || !hicon1)
        return;

    /* cast to IImageList */
    imgl1 = (IImageList *) himl1;
    imgl2 = (IImageList *) himl2;

    ret = -1;
    ok( IImageList_ReplaceIcon(imgl2, -1, hicon1, &ret) == S_OK && (ret == 0),"add icon1 to himl2 failed\n");

if (0)
{
    /* null cases that crash on native */
    IImageList_Merge(imgl1, -1, NULL, 0, 0, 0, &IID_IImageList, (void**)&merge);
    IImageList_Merge(imgl1, -1, (IUnknown*) imgl2, 0, 0, 0, &IID_IImageList, NULL);
}

    /* If himl1 has no images, merge still succeeds */
    hr = IImageList_Merge(imgl1, -1, (IUnknown *) imgl2, 0, 0, 0, &IID_IImageList, (void **) &merge);
    ok(hr == S_OK, "merge himl1,-1 failed\n");
    if (hr == S_OK) IImageList_Release(merge);

    hr = IImageList_Merge(imgl1, 0, (IUnknown *) imgl2, 0, 0, 0, &IID_IImageList, (void **) &merge);
    ok(hr == S_OK, "merge himl1,0 failed\n");
    if (hr == S_OK) IImageList_Release(merge);

    /* Same happens if himl2 is empty */
    IImageList_Release(imgl2);
    himl2 = pImageList_Create(32,32,0,0,3);
    ok(himl2 != NULL,"failed to recreate himl2\n");

    imgl2 = (IImageList *) himl2;

    hr = IImageList_Merge(imgl1, -1, (IUnknown *) imgl2, -1, 0, 0, &IID_IImageList, (void **) &merge);
    ok(hr == S_OK, "merge himl2,-1 failed\n");
    if (hr == S_OK) IImageList_Release(merge);

    hr = IImageList_Merge(imgl1, -1, (IUnknown *) imgl2, 0, 0, 0, &IID_IImageList, (void **) &merge);
    ok(hr == S_OK, "merge himl2,0 failed\n");
    if (hr == S_OK) IImageList_Release(merge);

    /* Now try merging an image with itself */
    ret = -1;
    ok( IImageList_ReplaceIcon(imgl2, -1, hicon1, &ret) == S_OK && (ret == 0),"re-add icon1 to himl2 failed\n");

    hr = IImageList_Merge(imgl2, 0, (IUnknown *) imgl2, 0, 0, 0, &IID_IImageList, (void **) &merge);
    ok(hr == S_OK, "merge himl2 with itself failed\n");
    if (hr == S_OK) IImageList_Release(merge);

    /* Try merging 2 different image lists */
    ret = -1;
    ok( IImageList_ReplaceIcon(imgl1, -1, hicon1, &ret) == S_OK && (ret == 0),"add icon1 to himl1 failed\n");

    hr = IImageList_Merge(imgl1, 0, (IUnknown *) imgl2, 0, 0, 0, &IID_IImageList, (void **) &merge);
    ok(hr == S_OK, "merge himl1 with himl2 failed\n");
    if (hr == S_OK) IImageList_Release(merge);

    hr = IImageList_Merge(imgl1, 0, (IUnknown *) imgl2, 0, 8, 16, &IID_IImageList, (void **) &merge);
    ok(hr == S_OK, "merge himl1 with himl2 8,16 failed\n");
    if (hr == S_OK) IImageList_Release(merge);

    IImageList_Release(imgl1);
    IImageList_Release(imgl2);

    DestroyIcon(hicon1);
    DestroyWindow(hwnd);
}