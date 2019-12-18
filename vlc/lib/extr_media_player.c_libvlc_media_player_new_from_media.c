#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  p_input_item; int /*<<< orphan*/  p_libvlc_instance; } ;
typedef  TYPE_1__ libvlc_media_t ;
struct TYPE_11__ {TYPE_1__* p_md; int /*<<< orphan*/  player; } ;
typedef  TYPE_2__ libvlc_media_player_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 TYPE_2__* libvlc_media_player_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_release (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_retain (TYPE_1__*) ; 
 int /*<<< orphan*/  media_attach_preparsed_event (TYPE_1__*) ; 
 int /*<<< orphan*/  media_detach_preparsed_event (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ ) ; 
 int vlc_player_SetCurrentMedia (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ ) ; 

libvlc_media_player_t *
libvlc_media_player_new_from_media( libvlc_media_t * p_md )
{
    libvlc_media_player_t * p_mi;

    p_mi = libvlc_media_player_new( p_md->p_libvlc_instance );
    if( !p_mi )
        return NULL;

    libvlc_media_retain( p_md );
    p_mi->p_md = p_md;
    media_attach_preparsed_event(p_md);

    vlc_player_Lock(p_mi->player);
    int ret = vlc_player_SetCurrentMedia(p_mi->player, p_md->p_input_item);
    vlc_player_Unlock(p_mi->player);

    if (ret != VLC_SUCCESS)
    {
        media_detach_preparsed_event(p_md);
        libvlc_media_release(p_md);
        p_mi->p_md = NULL;
        return NULL;
    }

    return p_mi;
}