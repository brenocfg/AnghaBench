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
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct vlc_player_track_priv {int vout_order; int /*<<< orphan*/ * vout; } ;
typedef  enum vlc_vout_order { ____Placeholder_vlc_vout_order } vlc_vout_order ;

/* Variables and functions */
 struct vlc_player_track_priv* vlc_player_GetPrivTrack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

vout_thread_t *
vlc_player_GetEsIdVout(vlc_player_t *player, vlc_es_id_t *es_id,
                       enum vlc_vout_order *order)
{
    struct vlc_player_track_priv *trackpriv =
        vlc_player_GetPrivTrack(player, es_id);
    if (trackpriv)
    {
        if (order)
            *order = trackpriv->vout_order;
        return trackpriv->vout;
    }
    return NULL;
}