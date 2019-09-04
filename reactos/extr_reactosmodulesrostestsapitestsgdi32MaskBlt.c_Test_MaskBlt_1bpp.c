#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int biWidth; } ;
struct TYPE_9__ {TYPE_1__ bmiHeader; } ;
struct TYPE_8__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_7; int member_8; int member_9; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int* PUCHAR ;
typedef  TYPE_4__* PBITMAPINFO ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKEROP4 (int,int) ; 
 int MERGEPAINT ; 
 int MaskBlt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int NOTSRCERASE ; 
 int PATCOPY ; 
 int SRCCOPY ; 
 int SRCINVERT ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghbmp24 ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void Test_MaskBlt_1bpp()
{
    HDC hdcDst, hdcSrc;
    struct
    {
        BITMAPINFOHEADER bmiHeader;
        ULONG aulColors[2];
    } bmiData = {{sizeof(BITMAPINFOHEADER), 8, 1, 1, 1, BI_RGB, 0, 10, 10, 2,0}, {0, 0xFFFFFF}};
    PBITMAPINFO pbmi = (PBITMAPINFO)&bmiData;
    HBITMAP hbmDst, hbmSrc, hbmMsk;
    PUCHAR pjBitsDst, pjBitsSrc, pjBitsMsk;
    BOOL ret;

    /* Create a dest dc and bitmap */
    hdcDst = CreateCompatibleDC(NULL);
    hbmDst = CreateDIBSection(hdcDst, pbmi, DIB_RGB_COLORS, (PVOID*)&pjBitsDst, NULL, 0);
    SelectObject(hdcDst, hbmDst);

    /* Create a source dc and bitmap */
    hdcSrc = CreateCompatibleDC(NULL);
    hbmSrc = CreateDIBSection(hdcSrc, pbmi, DIB_RGB_COLORS, (PVOID*)&pjBitsSrc, NULL, 0);
    SelectObject(hdcSrc, hbmSrc);

    /* Create a 1 bpp mask bitmap */
    hbmMsk = CreateDIBSection(hdcDst, pbmi, DIB_RGB_COLORS, (PVOID*)&pjBitsMsk, NULL, 0);

    /* Do the masking (SRCCOPY / NOOP) */
    pjBitsDst[0] = 0xAA;
    pjBitsSrc[0] = 0xCC;
    pjBitsMsk[0] = 0xF0;
    ret = MaskBlt(hdcDst, 0, 0, 8, 1, hdcSrc, 0, 0, hbmMsk, 0, 0, MAKEROP4(SRCCOPY, 0xAA0000));
    ok(ret == 1, "MaskBlt failed (%d)\n", ret);
    ok(pjBitsDst[0] == 0xCA, "pjBitsDst[0] == 0x%x\n", pjBitsDst[0]);

    pjBitsDst[0] = 0x00;
    pjBitsSrc[0] = 0xFF;
    pjBitsMsk[0] = 0xF0;
    ret = MaskBlt(hdcDst, 0, 0, 8, 1, hdcSrc, 0, 0, hbmMsk, 0, 0, MAKEROP4(SRCCOPY, 0xAA0000));
    ok(ret == 1, "MaskBlt failed (%d)\n", ret);
    ok(pjBitsDst[0] == 0xF0, "pjBitsDst[0] == 0x%x\n", pjBitsDst[0]);

    /* Do the masking (NOTSRCERASE / SRCINVERT) */
    pjBitsDst[0] = 0xF0; // 11110000
    pjBitsSrc[0] = 0xCC; // 11001100
    pjBitsMsk[0] = 0xAA; // 10101010

    ret = MaskBlt(hdcDst, 0, 0, 8, 1, hdcSrc, 0, 0, hbmMsk, 0, 0, MAKEROP4(NOTSRCERASE, SRCINVERT)); // 22
    ok(ret == 1, "MaskBlt failed (%d)\n", ret);
    ok(pjBitsDst[0] == 0x16, "pjBitsDst[0] == 0x%x\n", pjBitsDst[0]);

    /* Do the masking (MERGEPAINT / DSxn) */
    pjBitsDst[0] = 0xF0;
    pjBitsSrc[0] = 0xCC;
    pjBitsMsk[0] = 0xAA;
    ret = MaskBlt(hdcDst, 0, 0, 8, 1, hdcSrc, 0, 0, hbmMsk, 0, 0, MAKEROP4(MERGEPAINT, 0x990000));
    ok(ret == 1, "MaskBlt failed (%d)\n", ret);
    ok(pjBitsDst[0] == 0xE3, "pjBitsDst[0] == 0x%x\n", pjBitsDst[0]);

    /* Try a ROP that needs a mask with a NULL mask bitmap handle */
    ret = MaskBlt(hdcDst, 0, 0, 8, 1, hdcSrc, 0, 0, NULL, 0, 0, MAKEROP4(SRCCOPY, 0xAA0000));
    ok(ret == 1, "MaskBlt failed (%d)\n", ret);
    ok(pjBitsDst[0] == 0xCC, "pjBitsDst[0] == 0x%x\n", pjBitsDst[0]);

    /* Try a ROP that needs a mask with an invalid mask bitmap handle */
    ret = MaskBlt(hdcDst, 0, 0, 8, 1, hdcSrc, 0, 0, (HBITMAP)0x123456, 0, 0, MAKEROP4(SRCCOPY, 0xAA0000));
    ok(ret == 0, "MaskBlt should fail, but succeeded (%d)\n", ret);

    /* Try a ROP that needs a mask with an invalid mask bitmap */
    ok(ghbmp24 != NULL, "ghbmp24 is NULL!\n");
    ret = MaskBlt(hdcDst, 0, 0, 8, 1, hdcSrc, 0, 0, ghbmp24, 0, 0, MAKEROP4(SRCCOPY, 0xAA0000));
    ok(ret == 0, "MaskBlt should fail, but succeeded (%d)\n", ret);

    /* Try a ROP that needs no mask with an invalid mask bitmap */
    ret = MaskBlt(hdcDst, 0, 0, 8, 1, hdcSrc, 0, 0, (HBITMAP)0x123456, 0, 0, MAKEROP4(SRCCOPY, SRCCOPY));
    ok(ret == 1, "MaskBlt failed (%d)\n", ret);

    /* Try (PATCOPY / NOOP) with a NULL source mask and bitmap */
    ret = MaskBlt(hdcDst, 0, 0, 8, 1, NULL, 0, 0, NULL, 0, 0, MAKEROP4(PATCOPY, 0xAA0000));
    ok(ret == 0, "MaskBlt should fail, but succeeded (%d)\n", ret);


    /* Try with a mask that is smaller than the rect */
    DeleteObject(hbmMsk);
    pbmi->bmiHeader.biWidth = 4;
    hbmMsk = CreateDIBSection(hdcDst, pbmi, DIB_RGB_COLORS, (PVOID*)&pjBitsMsk, NULL, 0);

    /* Do the masking (SRCCOPY / NOOP) */
    pjBitsDst[0] = 0xAA; // 10101010
    pjBitsSrc[0] = 0xCC; // 11001100
    pjBitsMsk[0] = 0x33; // 00110011
    ret = MaskBlt(hdcDst, 0, 0, 5, 1, hdcSrc, 0, 0, hbmMsk, 0, 0, MAKEROP4(SRCCOPY, 0xAA0000));
    ok(ret == 0, "MaskBlt should fail, but succeeded (%d)\n", ret);
    ret = MaskBlt(hdcDst, 0, 0, 4, 1, hdcSrc, 0, 0, hbmMsk, 1, 0, MAKEROP4(SRCCOPY, 0xAA0000));
    ok(ret == 0, "MaskBlt should fail, but succeeded (%d)\n", ret);
    ret = MaskBlt(hdcDst, 0, 0, 4, 1, hdcSrc, 0, 0, hbmMsk, 0, 1, MAKEROP4(SRCCOPY, 0xAA0000));
    ok(ret == 0, "MaskBlt should fail, but succeeded (%d)\n", ret);
    ret = MaskBlt(hdcDst, 0, 0, 4, 1, hdcSrc, 0, 0, hbmMsk, 0, 0, MAKEROP4(SRCCOPY, 0xAA0000));
    ok(ret == 1, "MaskBlt failed (%d)\n", ret);
    ok(pjBitsDst[0] == 0x8A, "pjBitsDst[0] == 0x%x\n", pjBitsDst[0]);

}