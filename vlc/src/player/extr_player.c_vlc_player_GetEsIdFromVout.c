#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_5__ {size_t size; struct vlc_player_track_priv** data; } ;
typedef  TYPE_2__ vlc_player_track_vector ;
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct TYPE_4__ {int /*<<< orphan*/ * es_id; } ;
struct vlc_player_track_priv {TYPE_1__ t; int /*<<< orphan*/ * vout; } ;
struct vlc_player_input {int dummy; } ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_player_input_GetTrackVector (struct vlc_player_input*,int) ; 

vlc_es_id_t *
vlc_player_GetEsIdFromVout(vlc_player_t *player, vout_thread_t *vout)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    if (!input)
        return NULL;

    static const enum es_format_category_e cats[] = {
        VIDEO_ES, SPU_ES, AUDIO_ES /* for visualisation filters */
    };
    for (size_t i = 0; i < ARRAY_SIZE(cats); ++i)
    {
        enum es_format_category_e cat = cats[i];
        vlc_player_track_vector *vec =
            vlc_player_input_GetTrackVector(input, cat);
        for (size_t j = 0; j < vec->size; ++j)
        {
            struct vlc_player_track_priv *trackpriv = vec->data[j];
            if (trackpriv->vout == vout)
                return trackpriv->t.es_id;
        }
    }
    return NULL;
}