#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* p_next; } ;
typedef  TYPE_1__ subpicture_region_t ;
struct TYPE_10__ {scalar_t__ art; int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ epg_spu_updater_sys_t ;

/* Variables and functions */
 int ARGB_BGCOLOR ; 
 int OSDEPG_HEIGHT ; 
 int OSDEPG_LEFT ; 
 int OSDEPG_LOGO_SIZE ; 
 int OSDEPG_PADDING ; 
 int OSDEPG_TOP ; 
 int OSDEPG_WIDTH ; 
 int RGB_COLOR1 ; 
 int /*<<< orphan*/  vout_FillRightPanel (TYPE_2__*,int const,int,int const,int,int,int,TYPE_1__**) ; 
 TYPE_1__* vout_OSDBackground (int,int,int,int,int) ; 
 TYPE_1__* vout_OSDImage (int /*<<< orphan*/ ,int,int,int,int,scalar_t__) ; 

__attribute__((used)) static subpicture_region_t * vout_BuildOSDEpg(epg_spu_updater_sys_t *p_sys,
                                              int x, int y,
                                              int visible_width,
                                              int visible_height)
{
    subpicture_region_t *head;
    subpicture_region_t **last_ptr = &head;

    const int i_padding = visible_height * (OSDEPG_HEIGHT * OSDEPG_PADDING);

    *last_ptr = vout_OSDBackground(x + visible_width * OSDEPG_LEFT,
                                   y + visible_height * OSDEPG_TOP,
                                   visible_width  * OSDEPG_WIDTH,
                                   visible_height * OSDEPG_HEIGHT,
                                   ARGB_BGCOLOR);
    if(*last_ptr)
        last_ptr = &(*last_ptr)->p_next;

    struct
    {
        int x;
        int y;
        int w;
        int h;
        int rx;
        int ry;
    } panel = {
        x + visible_width  * OSDEPG_LEFT + i_padding,
        y + visible_height * OSDEPG_TOP + i_padding,
        visible_width  * OSDEPG_WIDTH - 2 * i_padding,
        visible_height * OSDEPG_HEIGHT - 2 * i_padding,
        visible_width * OSDEPG_LEFT + i_padding,
        visible_height * (1.0 - OSDEPG_TOP - OSDEPG_HEIGHT) + i_padding,
    };


    if( p_sys->art )
    {
        struct
        {
            int x;
            int y;
            int w;
            int h;
        } logo = {
            panel.x,
            panel.y,
            panel.h,
            panel.h,
        };

        *last_ptr = vout_OSDBackground(logo.x,
                                       logo.y,
                                       logo.w,
                                       logo.h,
                                       0xFF000000 | RGB_COLOR1);
        if(*last_ptr)
            last_ptr = &(*last_ptr)->p_next;

        int logo_padding = visible_height * (OSDEPG_LOGO_SIZE * OSDEPG_PADDING);
        *last_ptr = vout_OSDImage( p_sys->obj,
                                   logo.x + logo_padding,
                                   logo.y + logo_padding,
                                   logo.w - 2 * logo_padding,
                                   logo.h - 2 * logo_padding,
                                   p_sys->art );
        if(*last_ptr)
            last_ptr = &(*last_ptr)->p_next;

        /* shrink */
        panel.x += logo.w + i_padding;
        panel.w -= logo.w + i_padding;
    }

    vout_FillRightPanel( p_sys,
                         panel.x,
                         panel.y,
                         panel.w,
                         panel.h,
                         panel.rx,
                         panel.ry,
                         last_ptr );

    return head;
}