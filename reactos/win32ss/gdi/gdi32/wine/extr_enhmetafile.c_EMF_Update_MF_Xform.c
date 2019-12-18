#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {double eM11; double eM12; double eM21; double eM22; double eDx; double eDy; } ;
struct TYPE_9__ {TYPE_3__ world_transform; scalar_t__ wndOrgY; scalar_t__ vportOrgY; scalar_t__ wndOrgX; scalar_t__ vportOrgX; scalar_t__ wndExtY; scalar_t__ vportExtY; scalar_t__ wndExtX; scalar_t__ vportExtX; } ;
struct TYPE_10__ {TYPE_3__ init_transform; TYPE_1__ state; } ;
typedef  TYPE_2__ enum_emh_data ;
typedef  TYPE_3__ XFORM ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CombineTransform (TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  SetWorldTransform (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void EMF_Update_MF_Xform(HDC hdc, const enum_emh_data *info)
{
    XFORM mapping_mode_trans, final_trans;
    double scaleX, scaleY;

    scaleX = (double)info->state.vportExtX / (double)info->state.wndExtX;
    scaleY = (double)info->state.vportExtY / (double)info->state.wndExtY;
    mapping_mode_trans.eM11 = scaleX;
    mapping_mode_trans.eM12 = 0.0;
    mapping_mode_trans.eM21 = 0.0;
    mapping_mode_trans.eM22 = scaleY;
    mapping_mode_trans.eDx  = (double)info->state.vportOrgX - scaleX * (double)info->state.wndOrgX;
    mapping_mode_trans.eDy  = (double)info->state.vportOrgY - scaleY * (double)info->state.wndOrgY;

    CombineTransform(&final_trans, &info->state.world_transform, &mapping_mode_trans);
    CombineTransform(&final_trans, &final_trans, &info->init_transform);

    if (!SetWorldTransform(hdc, &final_trans))
    {
        ERR("World transform failed!\n");
    }
}