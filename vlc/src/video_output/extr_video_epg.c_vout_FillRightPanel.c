#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ i_id; float i_start; scalar_t__ i_duration; } ;
typedef  TYPE_2__ const vlc_epg_event_t ;
struct TYPE_14__ {int i_align; struct TYPE_14__* p_next; } ;
typedef  TYPE_3__ subpicture_region_t ;
struct TYPE_15__ {float time; TYPE_1__* epg; } ;
typedef  TYPE_4__ epg_spu_updater_sys_t ;
struct TYPE_12__ {char* psz_name; size_t i_event; TYPE_2__ const* p_current; TYPE_2__ const** pp_event; } ;

/* Variables and functions */
 int EPGOSD_TEXTSIZE_NAME ; 
 int EPGOSD_TEXTSIZE_NTWK ; 
 int EPGOSD_TEXTSIZE_PROG ; 
 int OSDEPG_ROW (int) ; 
 int OSDEPG_ROWS (int) ; 
 int RGB_COLOR1 ; 
 int SUBPICTURE_ALIGN_RIGHT ; 
 int SUBPICTURE_ALIGN_TOP ; 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_3__* vout_OSDEpgEvent (TYPE_2__ const*,int,int,int) ; 
 TYPE_3__* vout_OSDEpgSlider (int,int,int,int,float) ; 
 TYPE_3__* vout_OSDEpgText (char*,int,int,int,int) ; 
 char* vout_OSDPrintTime (float) ; 
 int /*<<< orphan*/  vout_OSDRegionConstrain (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vout_FillRightPanel(epg_spu_updater_sys_t *p_sys,
                                int x, int y,
                                int width, int height,
                                int rx, int ry,
                                subpicture_region_t **last_ptr)
{
    float f_progress = 0;
    VLC_UNUSED(ry);

    /* Display the name of the channel. */
    *last_ptr = vout_OSDEpgText(p_sys->epg->psz_name,
                                x,
                                y,
                                height * EPGOSD_TEXTSIZE_NAME,
                                0x00ffffff);
    if(*last_ptr)
        last_ptr = &(*last_ptr)->p_next;

    const vlc_epg_event_t *p_current = p_sys->epg->p_current;
    vlc_epg_event_t *p_next = NULL;
    if(!p_sys->epg->p_current && p_sys->epg->i_event)
        p_current = p_sys->epg->pp_event[0];

    for(size_t i=0; i<p_sys->epg->i_event; i++)
    {
        if( p_sys->epg->pp_event[i]->i_id != p_current->i_id )
        {
            p_next = p_sys->epg->pp_event[i];
            break;
        }
    }

    /* Display the name of the current program. */
    if(p_current)
    {
        *last_ptr = vout_OSDEpgEvent(p_current,
                                     x,
                                     y + height * OSDEPG_ROW(2),
                                     height * EPGOSD_TEXTSIZE_PROG);
        /* region rendering limits */
        vout_OSDRegionConstrain(*last_ptr, width, 0);
        if(*last_ptr)
            last_ptr = &(*last_ptr)->p_next;
    }

    /* NEXT EVENT */
    if(p_next)
    {
        *last_ptr = vout_OSDEpgEvent(p_next,
                                     x,
                                     y + height * OSDEPG_ROW(5),
                                     height * EPGOSD_TEXTSIZE_PROG);
        /* region rendering limits */
        vout_OSDRegionConstrain(*last_ptr, width, 0);
        if(*last_ptr)
            last_ptr = &(*last_ptr)->p_next;
    }

    if(p_sys->time)
    {
        f_progress = (p_sys->time - p_sys->epg->p_current->i_start) /
                     (float)p_sys->epg->p_current->i_duration;
    }

    /* Display the current program time slider. */
    *last_ptr = vout_OSDEpgSlider(x + width * 0.05,
                                  y + height * OSDEPG_ROW(9),
                                  width  * 0.90,
                                  height * OSDEPG_ROWS(1),
                                  f_progress);
    if (*last_ptr)
        last_ptr = &(*last_ptr)->p_next;

    /* Format the hours */
    if(p_sys->time)
    {
        char *psz_network = vout_OSDPrintTime(p_sys->time);
        if(psz_network)
        {
            *last_ptr = vout_OSDEpgText(psz_network,
                                        rx,
                                        y + height * OSDEPG_ROW(0),
                                        height * EPGOSD_TEXTSIZE_NTWK,
                                        RGB_COLOR1);
            free(psz_network);
            if(*last_ptr)
            {
                (*last_ptr)->i_align = SUBPICTURE_ALIGN_TOP|SUBPICTURE_ALIGN_RIGHT;
                last_ptr = &(*last_ptr)->p_next;
            }
        }
    }
}