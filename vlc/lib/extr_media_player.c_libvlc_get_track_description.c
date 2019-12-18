#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_track {int /*<<< orphan*/  name; int /*<<< orphan*/  es_id; } ;
struct TYPE_7__ {struct TYPE_7__* p_next; int /*<<< orphan*/  psz_name; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_1__ libvlc_track_description_t ;
struct TYPE_8__ {int /*<<< orphan*/ * player; } ;
typedef  TYPE_2__ libvlc_media_player_t ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_es_id_GetInputId (int /*<<< orphan*/ ) ; 
 struct vlc_player_track* vlc_player_GetTrackAt (int /*<<< orphan*/ *,int,size_t) ; 
 size_t vlc_player_GetTrackCount (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 

libvlc_track_description_t *
        libvlc_get_track_description( libvlc_media_player_t *p_mi,
                                      enum es_format_category_e cat )
{
    vlc_player_t *player = p_mi->player;
    vlc_player_Lock(player);

    libvlc_track_description_t *ret, **pp = &ret;

    size_t count = vlc_player_GetTrackCount(player, cat);
    for (size_t i = 0; i < count; i++)
    {
        libvlc_track_description_t *tr = malloc(sizeof (*tr));
        if (unlikely(tr == NULL))
        {
            libvlc_printerr("Not enough memory");
            continue;
        }

        const struct vlc_player_track *track =
            vlc_player_GetTrackAt(player, cat, i);

        *pp = tr;
        tr->i_id = vlc_es_id_GetInputId(track->es_id);
        tr->psz_name = strdup(track->name);
        if (unlikely(!tr->psz_name))
        {
            free(tr);
            continue;
        }
        pp = &tr->p_next;
    }

    *pp = NULL;

    vlc_player_Unlock(player);
    return ret;
}