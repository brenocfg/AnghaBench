#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  b_active; TYPE_2__* p_fontstyle; } ;
typedef  TYPE_3__ overlay_t ;
struct TYPE_15__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_16__ {int /*<<< orphan*/  b_updated; int /*<<< orphan*/  overlays; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_font_color; } ;
struct TYPE_17__ {TYPE_1__ fontstyle; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_6__ commandparams_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_features; int /*<<< orphan*/  i_font_color; } ;

/* Variables and functions */
 TYPE_3__* ListGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STYLE_HAS_FONT_COLOR ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (TYPE_6__*) ; 

__attribute__((used)) static int exec_SetTextColor( filter_t *p_filter,
                              const commandparams_t *p_params,
                              commandparams_t *p_results )
{
    VLC_UNUSED(p_results);
    filter_sys_t *p_sys = p_filter->p_sys;

    overlay_t *p_ovl = ListGet( &p_sys->overlays, p_params->i_id );
    if( p_ovl == NULL )
        return VLC_EGENERIC;

    p_ovl->p_fontstyle->i_font_color = p_params->fontstyle.i_font_color;
    p_ovl->p_fontstyle->i_features |= STYLE_HAS_FONT_COLOR;
    p_sys->b_updated = p_ovl->b_active;
    return VLC_SUCCESS;
}