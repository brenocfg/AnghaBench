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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_input {int /*<<< orphan*/ * cat_delays; } ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int AUDIO_ES ; 
 int SPU_ES ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 

vlc_tick_t
vlc_player_GetCategoryDelay(vlc_player_t *player, enum es_format_category_e cat)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);
    if (!input)
        return 0;

    if (cat != AUDIO_ES && cat != SPU_ES)
        return 0;

    return input->cat_delays[cat];
}