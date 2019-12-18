#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  scalar_t__ libvlc_media_slave_type_t ;
struct TYPE_3__ {int /*<<< orphan*/ * player; } ;
typedef  TYPE_1__ libvlc_media_player_t ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int AUDIO_ES ; 
 int SPU_ES ; 
 scalar_t__ libvlc_media_slave_type_subtitle ; 
 int vlc_player_AddAssociatedMedia (int /*<<< orphan*/ *,int,char const*,int,int,int) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 

int libvlc_media_player_add_slave( libvlc_media_player_t *p_mi,
                                   libvlc_media_slave_type_t i_type,
                                   const char *psz_uri, bool b_select )
{
    vlc_player_t *player = p_mi->player;
    vlc_player_Lock(player);

    enum es_format_category_e cat = i_type == libvlc_media_slave_type_subtitle
                                  ? SPU_ES
                                  : AUDIO_ES;

    int ret = vlc_player_AddAssociatedMedia(player, cat, psz_uri, b_select,
                                            false, false);

    vlc_player_Unlock(player);
    return ret;
}