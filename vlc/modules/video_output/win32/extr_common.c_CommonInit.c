#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ vout_display_t ;
typedef  int /*<<< orphan*/  vout_display_cfg_t ;
struct TYPE_7__ {int place_changed; int /*<<< orphan*/  texture_source; int /*<<< orphan*/  vdcfg; } ;
typedef  TYPE_2__ display_win32_area_t ;

/* Variables and functions */
 int VLC_VAR_BOOL ; 
 int VLC_VAR_DOINHERIT ; 
 int /*<<< orphan*/  var_Create (TYPE_1__*,char*,int) ; 

void CommonInit(vout_display_t *vd, display_win32_area_t *area, const vout_display_cfg_t *vdcfg)
{
    area->place_changed = false;
    area->vdcfg = *vdcfg;

    area->texture_source = vd->source;

    var_Create(vd, "disable-screensaver", VLC_VAR_BOOL | VLC_VAR_DOINHERIT);
}