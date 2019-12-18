#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* pf_update ) (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pf_validate ) (TYPE_2__*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ subpicture_updater_t ;
struct TYPE_8__ {int /*<<< orphan*/ * p_region; TYPE_3__* p_private; TYPE_1__ updater; } ;
typedef  TYPE_2__ subpicture_t ;
struct TYPE_9__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
typedef  TYPE_3__ subpicture_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subpicture_region_ChainDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  video_format_IsSimilar (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void subpicture_Update( subpicture_t *p_subpicture,
                        const video_format_t *p_fmt_src,
                        const video_format_t *p_fmt_dst,
                        vlc_tick_t i_ts )
{
    subpicture_updater_t *p_upd = &p_subpicture->updater;
    subpicture_private_t *p_private = p_subpicture->p_private;

    if( !p_upd->pf_validate )
        return;
    if( !p_upd->pf_validate( p_subpicture,
                          !video_format_IsSimilar( p_fmt_src,
                                                   &p_private->src ), p_fmt_src,
                          !video_format_IsSimilar( p_fmt_dst,
                                                   &p_private->dst ), p_fmt_dst,
                          i_ts ) )
        return;

    subpicture_region_ChainDelete( p_subpicture->p_region );
    p_subpicture->p_region = NULL;

    p_upd->pf_update( p_subpicture, p_fmt_src, p_fmt_dst, i_ts );

    video_format_Clean( &p_private->src );
    video_format_Clean( &p_private->dst );

    video_format_Copy( &p_private->src, p_fmt_src );
    video_format_Copy( &p_private->dst, p_fmt_dst );
}