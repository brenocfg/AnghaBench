#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int SourceConstantAlpha; int /*<<< orphan*/  AlphaFormat; scalar_t__ BlendFlags; int /*<<< orphan*/  BlendOp; } ;
struct TYPE_5__ {int /*<<< orphan*/  hdc; } ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_1__ GpGraphics ;
typedef  TYPE_2__ BLENDFUNCTION ;

/* Variables and functions */
 int /*<<< orphan*/  AC_SRC_ALPHA ; 
 int /*<<< orphan*/  AC_SRC_OVER ; 
 scalar_t__ DT_RASPRINTER ; 
 int /*<<< orphan*/  GdiAlphaBlend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__) ; 
 scalar_t__ GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SB_NONE ; 
 int /*<<< orphan*/  SHADEBLENDCAPS ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  StretchBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TECHNOLOGY ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static void gdi_alpha_blend(GpGraphics *graphics, INT dst_x, INT dst_y, INT dst_width, INT dst_height,
                            HDC hdc, INT src_x, INT src_y, INT src_width, INT src_height)
{
    if (GetDeviceCaps(graphics->hdc, TECHNOLOGY) == DT_RASPRINTER &&
        GetDeviceCaps(graphics->hdc, SHADEBLENDCAPS) == SB_NONE)
    {
        TRACE("alpha blending not supported by device, fallback to StretchBlt\n");

        StretchBlt(graphics->hdc, dst_x, dst_y, dst_width, dst_height,
                   hdc, src_x, src_y, src_width, src_height, SRCCOPY);
    }
    else
    {
        BLENDFUNCTION bf;

        bf.BlendOp = AC_SRC_OVER;
        bf.BlendFlags = 0;
        bf.SourceConstantAlpha = 255;
        bf.AlphaFormat = AC_SRC_ALPHA;

        GdiAlphaBlend(graphics->hdc, dst_x, dst_y, dst_width, dst_height,
                      hdc, src_x, src_y, src_width, src_height, bf);
    }
}