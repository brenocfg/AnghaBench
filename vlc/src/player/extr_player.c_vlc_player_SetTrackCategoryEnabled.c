#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_input {int /*<<< orphan*/ * thread; } ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;
struct TYPE_2__ {int /*<<< orphan*/  sout_var; int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int DATA_ES ; 
 int UNKNOWN_ES ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* cat2vars ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_player_UnselectTrackCategory (int /*<<< orphan*/ *,int) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 

void
vlc_player_SetTrackCategoryEnabled(vlc_player_t *player,
                                   enum es_format_category_e cat, bool enabled)
{
    assert(cat >= UNKNOWN_ES && cat <= DATA_ES);
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    var_SetBool(player, cat2vars[cat].var, enabled);
    var_SetBool(player, cat2vars[cat].sout_var, enabled);

    if (input)
    {
        var_SetBool(input->thread, cat2vars[cat].var, enabled);
        var_SetBool(input->thread, cat2vars[cat].sout_var, enabled);

        if (!enabled)
            vlc_player_UnselectTrackCategory(player, cat);
    }
}