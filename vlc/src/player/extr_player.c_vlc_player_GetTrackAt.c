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
struct TYPE_5__ {size_t size; TYPE_1__** data; } ;
typedef  TYPE_2__ vlc_player_track_vector ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_track {int dummy; } ;
struct vlc_player_input {int dummy; } ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;
struct TYPE_4__ {struct vlc_player_track const t; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_player_input_GetTrackVector (struct vlc_player_input*,int) ; 

const struct vlc_player_track *
vlc_player_GetTrackAt(vlc_player_t *player, enum es_format_category_e cat,
                      size_t index)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    if (!input)
        return NULL;
    vlc_player_track_vector *vec = vlc_player_input_GetTrackVector(input, cat);
    if (!vec)
        return NULL;
    assert(index < vec->size);
    return &vec->data[index]->t;
}