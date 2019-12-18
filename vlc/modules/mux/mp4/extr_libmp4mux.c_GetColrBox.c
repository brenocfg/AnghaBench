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
struct TYPE_3__ {scalar_t__ color_range; int /*<<< orphan*/  space; int /*<<< orphan*/  transfer; int /*<<< orphan*/  primaries; } ;
typedef  TYPE_1__ video_format_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 scalar_t__ COLOR_RANGE_FULL ; 
 int /*<<< orphan*/  bo_add_16be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_mem (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * box_new (char*) ; 
 int /*<<< orphan*/  vlc_coeffs_to_iso_23001_8_mc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_primaries_to_iso_23001_8_cp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_xfer_to_iso_23001_8_tc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bo_t *GetColrBox(const video_format_t *p_vfmt, bool b_mov)
{
    bo_t *p_box = box_new("colr");
    if(p_box)
    {
        bo_add_mem(p_box, 4, b_mov ? "nclc" : "nclx");
        bo_add_16be(p_box, vlc_primaries_to_iso_23001_8_cp(p_vfmt->primaries));
        bo_add_16be(p_box, vlc_xfer_to_iso_23001_8_tc(p_vfmt->transfer));
        bo_add_16be(p_box, vlc_coeffs_to_iso_23001_8_mc(p_vfmt->space));
        bo_add_8(p_box, p_vfmt->color_range == COLOR_RANGE_FULL ? 0x80 : 0x00);
    }
    return p_box;
}