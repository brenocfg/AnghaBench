#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  const* vlc_tick_t ;
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  const subpicture_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 

__attribute__((used)) static int TTML_ImageSpuValidate(subpicture_t *p_spu,
                                 bool b_src_changed, const video_format_t *p_fmt_src,
                                 bool b_dst_changed, const video_format_t *p_fmt_dst,
                                 vlc_tick_t ts)
{
    VLC_UNUSED(p_spu);
    VLC_UNUSED(b_src_changed); VLC_UNUSED(p_fmt_src);
    VLC_UNUSED(p_fmt_dst);
    VLC_UNUSED(ts);
    return b_dst_changed ? VLC_EGENERIC: VLC_SUCCESS;
}