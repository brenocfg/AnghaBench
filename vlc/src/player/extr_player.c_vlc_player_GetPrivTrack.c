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
typedef  int /*<<< orphan*/  vlc_player_track_vector ;
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct vlc_player_track_priv {int dummy; } ;
struct vlc_player_input {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_es_id_GetCat (int /*<<< orphan*/ *) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_player_input_GetTrackVector (struct vlc_player_input*,int /*<<< orphan*/ ) ; 
 struct vlc_player_track_priv* vlc_player_track_vector_FindById (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vlc_player_track_priv *
vlc_player_GetPrivTrack(vlc_player_t *player, vlc_es_id_t *id)

{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    if (!input)
        return NULL;
    vlc_player_track_vector *vec =
        vlc_player_input_GetTrackVector(input, vlc_es_id_GetCat(id));
    if (!vec)
        return NULL;
    return vlc_player_track_vector_FindById(vec, id, NULL);
}