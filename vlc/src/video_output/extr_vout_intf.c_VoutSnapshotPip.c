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
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_4__ {int b_ephemer; int b_fade; int i_original_picture_width; int i_original_picture_height; scalar_t__ i_start; scalar_t__ i_stop; scalar_t__ i_channel; } ;
typedef  TYPE_1__ subpicture_t ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_CODEC_YUVA ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 TYPE_1__* subpicture_NewFromPicture (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_now () ; 
 int /*<<< orphan*/  vout_PutSubpicture (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int VoutSnapshotPip( vout_thread_t *p_vout, picture_t *p_pic )
{
    subpicture_t *p_subpic = subpicture_NewFromPicture( VLC_OBJECT(p_vout),
                                                        p_pic, VLC_CODEC_YUVA );
    if( !p_subpic )
        return VLC_EGENERIC;

    /* FIXME SPU_DEFAULT_CHANNEL is not good (used by the text) but
     * hardcoded 0 doesn't seem right */
    p_subpic->i_channel = 0;
    p_subpic->i_start = vlc_tick_now();
    p_subpic->i_stop  = p_subpic->i_start + VLC_TICK_FROM_SEC(4);
    p_subpic->b_ephemer = true;
    p_subpic->b_fade = true;

    /* Reduce the picture to 1/4^2 of the screen */
    p_subpic->i_original_picture_width  *= 4;
    p_subpic->i_original_picture_height *= 4;

    vout_PutSubpicture( p_vout, p_subpic );
    return VLC_SUCCESS;
}