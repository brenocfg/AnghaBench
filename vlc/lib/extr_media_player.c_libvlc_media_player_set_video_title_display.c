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
typedef  size_t libvlc_position_t ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t libvlc_position_bottom_right ; 
 size_t libvlc_position_disable ; 
 unsigned int* position_subpicture_alignment ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,char*,unsigned int) ; 

void libvlc_media_player_set_video_title_display( libvlc_media_player_t *p_mi, libvlc_position_t position, unsigned timeout )
{
    assert( position >= libvlc_position_disable && position <= libvlc_position_bottom_right );

    if ( position != libvlc_position_disable )
    {
        var_SetBool( p_mi, "video-title-show", true );
        var_SetInteger( p_mi, "video-title-position", position_subpicture_alignment[position] );
        var_SetInteger( p_mi, "video-title-timeout", timeout );
    }
    else
    {
        var_SetBool( p_mi, "video-title-show", false );
    }
}