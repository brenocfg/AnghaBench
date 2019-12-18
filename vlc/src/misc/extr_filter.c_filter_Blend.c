#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* pf_video_blend ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int) ;int /*<<< orphan*/  p_module; } ;
typedef  TYPE_1__ vlc_blender_t ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int) ; 

int filter_Blend( vlc_blender_t *p_blend,
                  picture_t *p_dst, int i_dst_x, int i_dst_y,
                  const picture_t *p_src, int i_alpha )
{
    if( !p_blend->p_module )
        return VLC_EGENERIC;

    p_blend->pf_video_blend( p_blend, p_dst, p_src, i_dst_x, i_dst_y, i_alpha );
    return VLC_SUCCESS;
}