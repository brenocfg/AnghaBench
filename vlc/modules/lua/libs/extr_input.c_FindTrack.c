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
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_track {int /*<<< orphan*/  es_id; } ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int vlc_es_id_GetInputId (int /*<<< orphan*/ ) ; 
 struct vlc_player_track* vlc_player_GetTrackAt (int /*<<< orphan*/ *,int,size_t) ; 
 size_t vlc_player_GetTrackCount (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const struct vlc_player_track *
FindTrack(vlc_player_t *player, enum es_format_category_e cat, int id)
{
    size_t count = vlc_player_GetTrackCount(player, cat);
    for (size_t i = 0; i < count; ++i)
    {
        const struct vlc_player_track *track =
                vlc_player_GetTrackAt(player, cat, i);
        if (id == vlc_es_id_GetInputId(track->es_id))
            return track;
    }
    return NULL;
}