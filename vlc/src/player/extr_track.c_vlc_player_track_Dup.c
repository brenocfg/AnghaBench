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
struct vlc_player_track {int /*<<< orphan*/  selected; int /*<<< orphan*/  fmt; int /*<<< orphan*/  name; int /*<<< orphan*/  es_id; } ;
struct vlc_player_track_priv {struct vlc_player_track t; } ;

/* Variables and functions */
 struct vlc_player_track_priv* vlc_player_track_priv_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct vlc_player_track *
vlc_player_track_Dup(const struct vlc_player_track *src)
{
    struct vlc_player_track_priv *duppriv =
        vlc_player_track_priv_New(src->es_id, src->name, &src->fmt);

    if (!duppriv)
        return NULL;
    duppriv->t.selected = src->selected;
    return &duppriv->t;
}