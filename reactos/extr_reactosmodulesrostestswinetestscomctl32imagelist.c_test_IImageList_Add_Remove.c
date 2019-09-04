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
typedef  scalar_t__ HICON ;

/* Variables and functions */
 scalar_t__ CreateIcon (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DestroyIcon (scalar_t__) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IImageList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IImageList_Remove (int /*<<< orphan*/ *,int) ; 
 scalar_t__ IImageList_ReplaceIcon (int /*<<< orphan*/ *,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  ILC_COLOR16 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  hinst ; 
 int /*<<< orphan*/  icon_bits ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pImageList_Create (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_IImageList_Add_Remove(void)
{
    IImageList *imgl;
    HIMAGELIST himl;
    HRESULT hr;

    HICON hicon1;
    HICON hicon2;
    HICON hicon3;

    int ret;

    /* create an imagelist to play with */
    himl = pImageList_Create(84, 84, ILC_COLOR16, 0, 3);
    ok(himl != 0,"failed to create imagelist\n");

    imgl = (IImageList *) himl;

    /* load the icons to add to the image list */
    hicon1 = CreateIcon(hinst, 32, 32, 1, 1, icon_bits, icon_bits);
    ok(hicon1 != 0, "no hicon1\n");
    hicon2 = CreateIcon(hinst, 32, 32, 1, 1, icon_bits, icon_bits);
    ok(hicon2 != 0, "no hicon2\n");
    hicon3 = CreateIcon(hinst, 32, 32, 1, 1, icon_bits, icon_bits);
    ok(hicon3 != 0, "no hicon3\n");

    /* remove when nothing exists */
    hr = IImageList_Remove(imgl, 0);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    /* removing everything from an empty imagelist should succeed */
    hr = IImageList_Remove(imgl, -1);
    ok(hr == S_OK, "removed nonexistent icon\n");

    /* add three */
    ret = -1;
    ok( IImageList_ReplaceIcon(imgl, -1, hicon1, &ret) == S_OK && (ret == 0),"failed to add icon1\n");
    ret = -1;
    ok( IImageList_ReplaceIcon(imgl, -1, hicon2, &ret) == S_OK && (ret == 1),"failed to add icon2\n");
    ret = -1;
    ok( IImageList_ReplaceIcon(imgl, -1, hicon3, &ret) == S_OK && (ret == 2),"failed to add icon3\n");

    /* remove an index out of range */
    ok( IImageList_Remove(imgl, 4711) == E_INVALIDARG, "got 0x%08x\n", hr);

    /* remove three */
    ok( IImageList_Remove(imgl,0) == S_OK, "can't remove 0\n");
    ok( IImageList_Remove(imgl,0) == S_OK, "can't remove 0\n");
    ok( IImageList_Remove(imgl,0) == S_OK, "can't remove 0\n");

    /* remove one extra */
    ok( IImageList_Remove(imgl, 0) == E_INVALIDARG, "got 0x%08x\n", hr);

    IImageList_Release(imgl);
    ok(DestroyIcon(hicon1),"icon 1 wasn't deleted\n");
    ok(DestroyIcon(hicon2),"icon 2 wasn't deleted\n");
    ok(DestroyIcon(hicon3),"icon 3 wasn't deleted\n");
}