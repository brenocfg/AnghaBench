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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBitmap (int,int,int,int,int*) ; 
 int /*<<< orphan*/  CreatePatternBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATCOPY ; 
 int /*<<< orphan*/  PatBlt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gpulTargetBits ; 
 int /*<<< orphan*/  hdcTarget ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void Test_BrushOrigin()
{
    ULONG aulBits[2] = {0x5555AAAA, 0};
    HBITMAP hbmp;
    HBRUSH hbr;
    BOOL ret;

    hbmp = CreateBitmap(2, 2, 1, 1, aulBits);
    if (!hbmp)
    {
        printf("Couln not create a bitmap\n");
        return;
    }

    hbr = CreatePatternBrush(hbmp);
    if (!hbr)
    {
        printf("Couln not create a bitmap\n");
        return;
    }

    if (!SelectObject(hdcTarget, hbr))
    {
        printf("failed to select pattern brush\n");
        return;
    }

    ret = PatBlt(hdcTarget, 0, 0, 2, 2, PATCOPY);
    ok_long(ret, 1);
    ok_long(gpulTargetBits[0], 0xffffff);
    ok_long(gpulTargetBits[1], 0);
    ok_long(gpulTargetBits[16], 0);
    ok_long(gpulTargetBits[17], 0xffffff);
    //printf("0x%lx, 0x%lx\n", gpulTargetBits[0], gpulTargetBits[1]);

    ret = PatBlt(hdcTarget, 1, 0, 2, 2, PATCOPY);
    ok_long(ret, 1);
    ok_long(gpulTargetBits[0], 0xffffff);
    ok_long(gpulTargetBits[1], 0);
    ok_long(gpulTargetBits[2], 0xffffff);
    ok_long(gpulTargetBits[16], 0);
    ok_long(gpulTargetBits[17], 0xffffff);
    ok_long(gpulTargetBits[18], 0);

}