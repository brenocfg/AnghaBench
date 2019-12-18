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
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_6__ {int /*<<< orphan*/ * dither; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
#define  VOUT_DISPLAY_CHANGE_DISPLAY_FILLED 132 
#define  VOUT_DISPLAY_CHANGE_DISPLAY_SIZE 131 
#define  VOUT_DISPLAY_CHANGE_SOURCE_ASPECT 130 
#define  VOUT_DISPLAY_CHANGE_SOURCE_CROP 129 
#define  VOUT_DISPLAY_CHANGE_ZOOM 128 
 int /*<<< orphan*/  cucul_free_dither (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

__attribute__((used)) static int Control(vout_display_t *vd, int query, va_list args)
{
    vout_display_sys_t *sys = vd->sys;

    (void) args;

    switch (query) {
    case VOUT_DISPLAY_CHANGE_SOURCE_CROP:
        if (sys->dither)
            cucul_free_dither(sys->dither);
        sys->dither = NULL;
        /* fall through */
    case VOUT_DISPLAY_CHANGE_DISPLAY_SIZE:
    case VOUT_DISPLAY_CHANGE_ZOOM:
    case VOUT_DISPLAY_CHANGE_DISPLAY_FILLED:
    case VOUT_DISPLAY_CHANGE_SOURCE_ASPECT:
        return VLC_SUCCESS;

    default:
        msg_Err(vd, "Unsupported query in vout display caca");
        return VLC_EGENERIC;
    }
}