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
struct vlc_player_track {int /*<<< orphan*/ * es_id; scalar_t__ selected; } ;
struct vlc_player_input {int /*<<< orphan*/  thread; } ;
typedef  enum vlc_player_select_policy { ____Placeholder_vlc_player_select_policy } vlc_player_select_policy ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_CONTROL_SET_ES ; 
 int VLC_PLAYER_SELECT_EXCLUSIVE ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 scalar_t__ input_ControlPushEsHelper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** vlc_alloc (size_t,int) ; 
 int vlc_es_id_GetCat (int /*<<< orphan*/ *) ; 
 struct vlc_player_track* vlc_player_GetTrackAt (int /*<<< orphan*/ *,int const,size_t) ; 
 size_t vlc_player_GetTrackCount (int /*<<< orphan*/ *,int const) ; 
 unsigned int vlc_player_SelectEsIdList (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ **) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_osd_Track (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

unsigned
vlc_player_SelectEsId(vlc_player_t *player, vlc_es_id_t *id,
                      enum vlc_player_select_policy policy)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);
    if (!input)
        return 0;

    if (policy == VLC_PLAYER_SELECT_EXCLUSIVE)
        goto select_one;

    /* VLC_PLAYER_SELECT_SIMULTANEOUS */
    const enum es_format_category_e cat = vlc_es_id_GetCat(id);
    const size_t track_count = vlc_player_GetTrackCount(player, cat);

    if (track_count == 0)
        return 0;

    size_t selected_track_count = 1;
    for (size_t i = 0; i < track_count; ++i)
    {
        const struct vlc_player_track *track =
            vlc_player_GetTrackAt(player, cat, i);
        if (track->selected && track->es_id != id)
            selected_track_count++;
    }

    if (selected_track_count == 1)
        goto select_one;

    vlc_es_id_t **es_id_list =
        vlc_alloc(selected_track_count + 1, sizeof(vlc_es_id_t*));
    if (!es_id_list)
        return 0;

    size_t es_id_list_idx = 0;
    /* Assure to select the requeste track */
    es_id_list[es_id_list_idx++] = id;

    for (size_t i = 0; i < track_count; ++i)
    {
        const struct vlc_player_track *track =
            vlc_player_GetTrackAt(player, cat, i);
        if (track->selected && track->es_id != id)
            es_id_list[es_id_list_idx++] = track->es_id;
    }
    es_id_list[selected_track_count] = NULL;

    unsigned ret = vlc_player_SelectEsIdList(player, cat, es_id_list);
    free(es_id_list);
    return ret;

select_one:
    if (input_ControlPushEsHelper(input->thread, INPUT_CONTROL_SET_ES, id)
     == VLC_SUCCESS)
        vlc_player_osd_Track(player, id, true);
    return 1;

}