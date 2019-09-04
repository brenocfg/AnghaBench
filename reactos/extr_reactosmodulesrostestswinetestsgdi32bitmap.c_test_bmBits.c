#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bmp ;
typedef  int /*<<< orphan*/  bits ;
struct TYPE_6__ {int /*<<< orphan*/  bmBits; } ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  TYPE_1__ BYTE ;
typedef  TYPE_1__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateBitmap (int,int,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int GetObjectW (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_bmBits(void)
{
    BYTE bits[4];
    HBITMAP hbmp;
    BITMAP bmp;

    memset(bits, 0, sizeof(bits));
    hbmp = CreateBitmap(2, 2, 1, 4, bits);
    ok(hbmp != NULL, "CreateBitmap failed\n");

    memset(&bmp, 0xFF, sizeof(bmp));
    ok(GetObjectW(hbmp, sizeof(bmp), &bmp) == sizeof(bmp),
       "GetObject failed or returned a wrong structure size\n");
    ok(!bmp.bmBits, "bmBits must be NULL for device-dependent bitmaps\n");

    DeleteObject(hbmp);
}