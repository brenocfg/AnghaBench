#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  imldp ;
struct TYPE_4__ {int y; int x; int /*<<< orphan*/  i; void* rgbFg; void* rgbBk; int /*<<< orphan*/  fStyle; scalar_t__ himl; int /*<<< orphan*/ * hdcDst; int /*<<< orphan*/  cbSize; } ;
typedef  TYPE_1__ IMAGELISTDRAWPARAMS ;
typedef  int /*<<< orphan*/  IImageList ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HIMAGELIST ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  scalar_t__ HBITMAP ;

/* Variables and functions */
 void* CLR_DEFAULT ; 
 scalar_t__ CreateBitmap (int,int,int,int,int /*<<< orphan*/ ) ; 
 int DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ IImageList_Add (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ IImageList_Draw (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IImageList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IImageList_Remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IImageList_Replace (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IImageList_SetImageCount (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ILC_COLOR16 ; 
 int /*<<< orphan*/  IMAGELISTDRAWPARAMS_V3_SIZE ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  bitmap_bits ; 
 int /*<<< orphan*/  create_window () ; 
 int /*<<< orphan*/  force_redraw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pImageList_Create (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_IImageList_Draw(void)
{
    IImageList *imgl;
    HIMAGELIST himl;

    HBITMAP hbm1;
    HBITMAP hbm2;
    HBITMAP hbm3;

    IMAGELISTDRAWPARAMS imldp;
    HWND hwndfortest;
    HRESULT hr;
    HDC hdc;
    int ret;

    hwndfortest = create_window();
    hdc = GetDC(hwndfortest);
    ok(hdc!=NULL, "couldn't get DC\n");

    /* create an imagelist to play with */
    himl = pImageList_Create(48, 48, ILC_COLOR16, 0, 3);
    ok(himl!=0,"failed to create imagelist\n");

    imgl = (IImageList *) himl;

    /* load the icons to add to the image list */
    hbm1 = CreateBitmap(48, 48, 1, 1, bitmap_bits);
    ok(hbm1 != 0, "no bitmap 1\n");
    hbm2 = CreateBitmap(48, 48, 1, 1, bitmap_bits);
    ok(hbm2 != 0, "no bitmap 2\n");
    hbm3 = CreateBitmap(48, 48, 1, 1, bitmap_bits);
    ok(hbm3 != 0, "no bitmap 3\n");

    /* add three */
    ret = -1;
    ok( IImageList_Add(imgl, hbm1, 0, &ret) == S_OK && (ret == 0), "failed to add bitmap 1\n");
    ret = -1;
    ok( IImageList_Add(imgl, hbm2, 0, &ret) == S_OK && (ret == 1), "failed to add bitmap 2\n");

    ok( IImageList_SetImageCount(imgl, 3) == S_OK, "Setimage count failed\n");
    ok( IImageList_Replace(imgl, 2, hbm3, 0) == S_OK, "failed to replace bitmap 3\n");

if (0)
{
    /* crashes on native */
    IImageList_Draw(imgl, NULL);
}

    memset(&imldp, 0, sizeof (imldp));
    hr = IImageList_Draw(imgl, &imldp);
    ok( hr == E_INVALIDARG, "got 0x%08x\n", hr);

    imldp.cbSize = IMAGELISTDRAWPARAMS_V3_SIZE;
    imldp.hdcDst = hdc;
    imldp.himl = himl;

    force_redraw(hwndfortest);

    imldp.fStyle = SRCCOPY;
    imldp.rgbBk = CLR_DEFAULT;
    imldp.rgbFg = CLR_DEFAULT;
    imldp.y = 100;
    imldp.x = 100;
    ok( IImageList_Draw(imgl, &imldp) == S_OK, "should succeed\n");
    imldp.i ++;
    ok( IImageList_Draw(imgl, &imldp) == S_OK, "should succeed\n");
    imldp.i ++;
    ok( IImageList_Draw(imgl, &imldp) == S_OK, "should succeed\n");
    imldp.i ++;
    ok( IImageList_Draw(imgl, &imldp) == E_INVALIDARG, "should fail\n");

    /* remove three */
    ok( IImageList_Remove(imgl, 0) == S_OK, "removing 1st bitmap\n");
    ok( IImageList_Remove(imgl, 0) == S_OK, "removing 2nd bitmap\n");
    ok( IImageList_Remove(imgl, 0) == S_OK, "removing 3rd bitmap\n");

    /* destroy it */
    IImageList_Release(imgl);

    /* bitmaps should not be deleted by the imagelist */
    ok(DeleteObject(hbm1),"bitmap 1 can't be deleted\n");
    ok(DeleteObject(hbm2),"bitmap 2 can't be deleted\n");
    ok(DeleteObject(hbm3),"bitmap 3 can't be deleted\n");

    ReleaseDC(hwndfortest, hdc);
    DestroyWindow(hwndfortest);
}