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
struct TYPE_5__ {size_t size; struct vlc_player_track_priv** data; } ;
typedef  TYPE_2__ vlc_player_track_vector ;
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct TYPE_4__ {int /*<<< orphan*/ * es_id; } ;
struct vlc_player_track_priv {TYPE_1__ t; } ;

/* Variables and functions */

struct vlc_player_track_priv *
vlc_player_track_vector_FindById(vlc_player_track_vector *vec, vlc_es_id_t *id,
                                 size_t *idx)
{
    for (size_t i = 0; i < vec->size; ++i)
    {
        struct vlc_player_track_priv *trackpriv = vec->data[i];
        if (trackpriv->t.es_id == id)
        {
            if (idx)
                *idx = i;
            return trackpriv;
        }
    }
    return NULL;
}