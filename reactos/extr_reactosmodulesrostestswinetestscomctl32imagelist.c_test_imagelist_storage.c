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
typedef  scalar_t__ HIMAGELIST ;
typedef  int /*<<< orphan*/  HICON ;
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int BMP_CX ; 
 int /*<<< orphan*/  CreateIcon (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ ) ; 
 int ILC_COLOR24 ; 
 int ILC_COLOR4 ; 
 int ILC_COLOR8 ; 
 int ILC_MASK ; 
 int TRUE ; 
 int /*<<< orphan*/  check_iml_data (scalar_t__,int,int,int,int,int,int,char*) ; 
 int /*<<< orphan*/  create_bitmap (int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hinst ; 
 int /*<<< orphan*/  icon_bits ; 
 int /*<<< orphan*/  image_list_init (scalar_t__,int) ; 
 int /*<<< orphan*/  is_v6_test () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pImageList_Add (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pImageList_Create (int,int,int,int,int) ; 
 int pImageList_Destroy (scalar_t__) ; 
 int pImageList_Remove (scalar_t__,int) ; 
 int pImageList_ReplaceIcon (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int pImageList_SetImageCount (scalar_t__,int) ; 

__attribute__((used)) static void test_imagelist_storage(void)
{
    HIMAGELIST himl;
    INT ret, grow;
    HBITMAP hbm;
    HICON icon;

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24, 1, 1);
    ok(himl != 0, "ImageList_Create failed\n");

    check_iml_data(himl, BMP_CX, BMP_CX, 0, 2, 1, ILC_COLOR24, "empty");

    image_list_init(himl, 1);
    check_iml_data(himl, BMP_CX, BMP_CX, 24, 27, 1, ILC_COLOR24, "orig");

    ret = pImageList_Remove(himl, 4);
    ok(ret, "ImageList_Remove failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 23, 27, 1, ILC_COLOR24, "1");

    ret = pImageList_Remove(himl, 5);
    ok(ret, "ImageList_Remove failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 22, 27, 1, ILC_COLOR24, "2");

    ret = pImageList_Remove(himl, 6);
    ok(ret, "ImageList_Remove failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 21, 27, 1, ILC_COLOR24, "3");

    ret = pImageList_Remove(himl, 7);
    ok(ret, "ImageList_Remove failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 20, 27, 1, ILC_COLOR24, "4");

    ret = pImageList_Remove(himl, -2);
    ok(!ret, "ImageList_Remove(-2) should fail\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 20, 27, 1, ILC_COLOR24, "5");

    ret = pImageList_Remove(himl, 20);
    ok(!ret, "ImageList_Remove(20) should fail\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 20, 27, 1, ILC_COLOR24, "6");

    ret = pImageList_Remove(himl, -1);
    ok(ret, "ImageList_Remove(-1) failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 4, 1, ILC_COLOR24, "7");

    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    /* test ImageList_Create storage allocation */

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24, 0, 32);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 1, 32, ILC_COLOR24, "init 0 grow 32");
    hbm = create_bitmap(BMP_CX * 9, BMP_CX, 0, "9");
    ret = pImageList_Add(himl, hbm, NULL);
    ok(ret == 0, "ImageList_Add returned %d, expected 0\n", ret);
    check_iml_data(himl, BMP_CX, BMP_CX, 1, 34, 32, ILC_COLOR24, "add 1 x 9");
    DeleteObject(hbm);
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24, 4, 4);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 5, 4, ILC_COLOR24, "init 4 grow 4");
    hbm = create_bitmap(BMP_CX, BMP_CX * 9, 0, "9");
    ret = pImageList_Add(himl, hbm, NULL);
    ok(ret == 0, "ImageList_Add returned %d, expected 0\n", ret);
    check_iml_data(himl, BMP_CX, BMP_CX, 9, 15, 4, ILC_COLOR24, "add 9 x 1");
    ret = pImageList_Add(himl, hbm, NULL);
    ok(ret == 9, "ImageList_Add returned %d, expected 9\n", ret);
    check_iml_data(himl, BMP_CX, BMP_CX, 18, 25, 4, ILC_COLOR24, "add 9 x 1");
    DeleteObject(hbm);
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24, 207, 209);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 208, 209, ILC_COLOR24, "init 207 grow 209");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24, 209, 207);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 210, 207, ILC_COLOR24, "init 209 grow 207");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24, 14, 4);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 15, 4, ILC_COLOR24, "init 14 grow 4");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24, 5, 9);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 6, 9, ILC_COLOR24, "init 5 grow 9");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24, 9, 5);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 10, 5, ILC_COLOR24, "init 9 grow 5");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24, 2, 4);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 3, 4, ILC_COLOR24, "init 2 grow 4");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24, 4, 2);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 5, 2, ILC_COLOR24, "init 4 grow 2");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR8, 4, 2);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 5, 2, ILC_COLOR8, "bpp 8");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR4, 4, 2);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 5, 2, ILC_COLOR4, "bpp 4");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, 0, 4, 2);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 5, 2, ILC_COLOR4, "bpp default");
    icon = CreateIcon(hinst, 32, 32, 1, 1, icon_bits, icon_bits);
    ok( pImageList_ReplaceIcon(himl, -1, icon) == 0, "Failed to add icon.\n");
    ok( pImageList_ReplaceIcon(himl, -1, icon) == 1, "Failed to add icon.\n");
    DestroyIcon( icon );
    check_iml_data(himl, BMP_CX, BMP_CX, 2, 5, 2, ILC_COLOR4, "bpp default");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR24|ILC_MASK, 4, 2);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 5, 2, ILC_COLOR24|ILC_MASK, "bpp 24 + mask");
    icon = CreateIcon(hinst, 32, 32, 1, 1, icon_bits, icon_bits);
    ok( pImageList_ReplaceIcon(himl, -1, icon) == 0, "Failed to add icon.\n");
    ok( pImageList_ReplaceIcon(himl, -1, icon) == 1, "Failed to add icon.\n");
    DestroyIcon( icon );
    check_iml_data(himl, BMP_CX, BMP_CX, 2, 5, 2, ILC_COLOR24|ILC_MASK, "bpp 24 + mask");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR4|ILC_MASK, 4, 2);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 5, 2, ILC_COLOR4|ILC_MASK, "bpp 4 + mask");
    icon = CreateIcon(hinst, 32, 32, 1, 1, icon_bits, icon_bits);
    ok( pImageList_ReplaceIcon(himl, -1, icon) == 0, "Failed to add icon.\n");
    ok( pImageList_ReplaceIcon(himl, -1, icon) == 1, "Failed to add icon.\n");
    DestroyIcon( icon );
    check_iml_data(himl, BMP_CX, BMP_CX, 2, 5, 2, ILC_COLOR4|ILC_MASK, "bpp 4 + mask");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR4|ILC_MASK, 2, 99);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 3, 99, ILC_COLOR4|ILC_MASK, "init 2 grow 99");
    icon = CreateIcon(hinst, 32, 32, 1, 1, icon_bits, icon_bits);
    ok( pImageList_ReplaceIcon(himl, -1, icon) == 0, "Failed to add icon.\n");
    ok( pImageList_ReplaceIcon(himl, -1, icon) == 1, "Failed to add icon.\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 2, 3, 99, ILC_COLOR4|ILC_MASK, "init 2 grow 99 2 icons");
    ok( pImageList_ReplaceIcon(himl, -1, icon) == 2, "Failed to add icon\n");
    DestroyIcon( icon );
    check_iml_data(himl, BMP_CX, BMP_CX, 3, 104, 99, ILC_COLOR4|ILC_MASK, "init 2 grow 99 3 icons");
    ok( pImageList_Remove(himl, -1) == TRUE, "Failed to remove icon.\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 100, 99, ILC_COLOR4|ILC_MASK, "init 2 grow 99 empty");
    ok( pImageList_SetImageCount(himl, 22) == TRUE, "Failed to set image count.\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 22, 23, 99, ILC_COLOR4|ILC_MASK, "init 2 grow 99 set count 22");
    ok( pImageList_SetImageCount(himl, 0) == TRUE, "Failed to set image count.\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 1, 99, ILC_COLOR4|ILC_MASK, "init 2 grow 99 set count 0");
    ok( pImageList_SetImageCount(himl, 42) == TRUE, "Failed to set image count.\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 42, 43, 99, ILC_COLOR4|ILC_MASK, "init 2 grow 99 set count 42");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    for (grow = 1; grow <= 16; grow++)
    {
        himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR4|ILC_MASK, 2, grow);
        ok(himl != 0, "ImageList_Create failed\n");
        check_iml_data(himl, BMP_CX, BMP_CX, 0, 3, grow, ILC_COLOR4|ILC_MASK, "grow test");
        ret = pImageList_Destroy(himl);
        ok(ret, "ImageList_Destroy failed\n");
    }

    himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR4|ILC_MASK, 2, -20);
    ok(himl != 0, "ImageList_Create failed\n");
    check_iml_data(himl, BMP_CX, BMP_CX, 0, 3, -20, ILC_COLOR4|ILC_MASK, "init 2 grow -20");
    ret = pImageList_Destroy(himl);
    ok(ret, "ImageList_Destroy failed\n");

    /* Version 6 implementation hangs on large grow values. */
    if (!is_v6_test())
    {
        himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR4|ILC_MASK, 2, 65536+12);
        ok(himl != 0, "ImageList_Create failed\n");
        check_iml_data(himl, BMP_CX, BMP_CX, 0, 3, 65536+12, ILC_COLOR4|ILC_MASK, "init 2 grow 65536+12");
        ret = pImageList_Destroy(himl);
        ok(ret, "ImageList_Destroy failed\n");

        himl = pImageList_Create(BMP_CX, BMP_CX, ILC_COLOR4|ILC_MASK, 2, 65535);
        ok(himl != 0, "ImageList_Create failed\n");
        check_iml_data(himl, BMP_CX, BMP_CX, 0, 3, 65535, ILC_COLOR4|ILC_MASK, "init 2 grow 65535");
        ret = pImageList_Destroy(himl);
        ok(ret, "ImageList_Destroy failed\n");
    }
}