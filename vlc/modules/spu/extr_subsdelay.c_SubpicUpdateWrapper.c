#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  double vlc_tick_t ;
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_12__ {double i_new_stop; TYPE_6__* p_source; TYPE_3__* p_subpic; } ;
typedef  TYPE_4__ subsdelay_heap_entry_t ;
struct TYPE_9__ {TYPE_4__* p_sys; } ;
struct TYPE_13__ {TYPE_1__ updater; } ;
typedef  TYPE_5__ subpicture_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* pf_update ) (TYPE_6__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,double) ;} ;
struct TYPE_14__ {double i_start; double i_stop; int /*<<< orphan*/  p_region; TYPE_2__ updater; } ;
struct TYPE_11__ {int /*<<< orphan*/  p_region; } ;

/* Variables and functions */
 int /*<<< orphan*/  SubpicLocalUpdate (TYPE_5__*,double) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,double) ; 

__attribute__((used)) static void SubpicUpdateWrapper( subpicture_t *p_subpic, const video_format_t *p_fmt_src,
                                  const video_format_t *p_fmt_dst, vlc_tick_t i_ts )
{
    subsdelay_heap_entry_t *p_entry;
    vlc_tick_t i_new_ts;

    p_entry = p_subpic->updater.p_sys;
    if( !p_entry )
    {
        return;
    }

    /* call source update */
    if( p_entry->p_source->updater.pf_update )
    {
        i_new_ts = p_entry->p_source->i_start +
                   ( (double)( p_entry->p_source->i_stop - p_entry->p_source->i_start ) * ( i_ts - p_entry->p_source->i_start ) ) /
                   ( p_entry->i_new_stop - p_entry->p_source->i_start );

        p_entry->p_source->p_region = p_entry->p_subpic->p_region;

        p_entry->p_source->updater.pf_update( p_entry->p_source, p_fmt_src, p_fmt_dst, i_new_ts );

        p_entry->p_subpic->p_region = p_entry->p_source->p_region;
    }

    SubpicLocalUpdate( p_subpic, i_ts );
}