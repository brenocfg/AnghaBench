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
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct vlc_player_track {char* name; } ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 char* es_format_category_to_string (int) ; 
 int vlc_es_id_GetCat (int /*<<< orphan*/ *) ; 
 struct vlc_player_track* vlc_player_GetTrack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_osd_Message (int /*<<< orphan*/ *,char*,char const*,char const*) ; 

void
vlc_player_osd_Track(vlc_player_t *player, vlc_es_id_t *id, bool select)
{
    enum es_format_category_e cat = vlc_es_id_GetCat(id);
    const struct vlc_player_track *track = vlc_player_GetTrack(player, id);
    if (!track && select)
        return;

    const char *cat_name = es_format_category_to_string(cat);
    assert(cat_name);
    const char *track_name = select ? track->name : _("N/A");
    vlc_player_osd_Message(player, _("%s track: %s"), cat_name, track_name);
}