#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_3__ {int member_0; int member_2; int member_12; int member_16; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ IMAGELISTDRAWPARAMS ;
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_NONE ; 
 int ILD_IMAGE ; 
 int ILD_ROP ; 
 int /*<<< orphan*/  ILS_NORMAL ; 
 int /*<<< orphan*/  check_ImageList_DrawIndirect (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void check_ImageList_DrawIndirect_ILD_ROP(HDC hdc, HIMAGELIST himl, UINT32 *bits, int i,
                                                DWORD dwRop, UINT32 expected, int line)
{
    IMAGELISTDRAWPARAMS ildp = {sizeof(IMAGELISTDRAWPARAMS), himl, i, hdc,
        0, 0, 0, 0, 0, 0, CLR_NONE, CLR_NONE, ILD_IMAGE | ILD_ROP, dwRop, ILS_NORMAL, 0, 0x00000000};
    check_ImageList_DrawIndirect(&ildp, bits, expected, line);
}