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
typedef  scalar_t__ HDC ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateICA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int MAKEROP4 (int,int) ; 
 int PATCOPY ; 
 int PATINVERT ; 
 int PatBlt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int SRCCOPY ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ hdcTarget ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_long (int,int) ; 

void Test_PatBlt_Params()
{
    BOOL ret;
    ULONG i, rop;
    HDC hdc;

    /* Test a rop that contains only the operation index */
    ret = PatBlt(hdcTarget, 0, 0, 1, 1, PATCOPY & 0x00FF0000);
    ok_long(ret, 1);

    /* Test a rop that contains arbitrary values outside the operation index */
    ret = PatBlt(hdcTarget, 0, 0, 1, 1, (PATCOPY & 0x00FF0000) | 0xab00cdef);
    ok_long(ret, 1);

    /* Test an invalid rop  */
    SetLastError(0);
    ok_long(PatBlt(hdcTarget, 0, 0, 1, 1, SRCCOPY) , 0);
    ok_err(0);

    /* Test all rops */
    for (i = 0; i < 256; i++)
    {
        rop = i << 16;
        ret = PatBlt(hdcTarget, 0, 0, 1, 1, rop);

        /* Only these should succeed (they use no source) */
        if ((i == 0) || (i == 5) || (i == 10) || (i == 15) || (i == 80) ||
            (i == 85) || (i == 90) || (i == 95) || (i == 160) || (i == 165) ||
            (i == 170) || (i == 175) || (i == 240) || (i == 245) ||
            (i == 250) || (i == 255))
        {
            ok(ret == 1, "index %ld failed, but should succeed\n", i);
        }
        else
        {
            ok(ret == 0, "index %ld succeeded, but should fail\n", i);
        }
    }

    /* Test quaternary rop, the background part is simply ignored */
    ret = PatBlt(hdcTarget, 0, 0, 1, 1, MAKEROP4(PATCOPY, PATINVERT));
    ok_long(ret, 1);
    ret = PatBlt(hdcTarget, 0, 0, 1, 1, MAKEROP4(PATCOPY, SRCCOPY));
    ok_long(ret, 1);
    ret = PatBlt(hdcTarget, 0, 0, 1, 1, MAKEROP4(SRCCOPY, PATCOPY));
    ok_long(ret, 0);

    /* Test an info DC */
    hdc = CreateICA("DISPLAY", NULL, NULL, NULL);
    ok(hdc != 0, "\n");
    SetLastError(0);
    ok_long(PatBlt(hdc, 0, 0, 1, 1, PATCOPY), 1);
    ok_err(0);
    DeleteDC(hdc);

    /* Test a mem DC without selecting a bitmap */
    hdc = CreateCompatibleDC(NULL);
    ok(hdc != 0, "\n");
    ok_long(PatBlt(hdc, 0, 0, 1, 1, PATCOPY), 1);
    ok_err(0);
    DeleteDC(hdc);



}