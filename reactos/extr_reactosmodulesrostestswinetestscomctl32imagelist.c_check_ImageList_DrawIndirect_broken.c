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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int member_0; int member_2; int member_16; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ IMAGELISTDRAWPARAMS ;
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_NONE ; 
 scalar_t__ broken (scalar_t__) ; 
 scalar_t__ colour_match (int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int,int) ; 
 int /*<<< orphan*/  pImageList_DrawIndirect (TYPE_1__*) ; 

__attribute__((used)) static void check_ImageList_DrawIndirect_broken(HDC hdc, HIMAGELIST himl, UINT32 *bits, int i,
                                                UINT fStyle, UINT fState, DWORD Frame, UINT32 expected,
                                                UINT32 broken_expected, int line)
{
    IMAGELISTDRAWPARAMS ildp = {sizeof(IMAGELISTDRAWPARAMS), himl, i, hdc,
        0, 0, 0, 0, 0, 0, CLR_NONE, CLR_NONE, fStyle, 0, fState, Frame, 0x00000000};
    bits[0] = 0x00FFFFFF;
    pImageList_DrawIndirect(&ildp);
    ok(colour_match(bits[0], expected) ||
       broken(colour_match(bits[0], broken_expected)),
       "ImageList_DrawIndirect: Pixel %08X, Expected a close match to %08X from line %d\n",
       bits[0] & 0x00FFFFFF, expected, line);
}