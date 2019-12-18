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
struct vlc_player_track {int dummy; } ;
struct report_track_list {int action; int /*<<< orphan*/  track; } ;
struct ctx {int dummy; } ;
typedef  enum vlc_player_list_action { ____Placeholder_vlc_player_list_action } vlc_player_list_action ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_PUSH (int /*<<< orphan*/ ,struct report_track_list) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct ctx* get_ctx (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  on_track_list_changed ; 
 int /*<<< orphan*/  vlc_player_track_Dup (struct vlc_player_track const*) ; 

__attribute__((used)) static void
player_on_track_list_changed(vlc_player_t *player,
                             enum vlc_player_list_action action,
                             const struct vlc_player_track *track,
                             void *data)
{
    struct ctx *ctx = get_ctx(player, data);
    struct report_track_list report = {
        .action = action,
        .track = vlc_player_track_Dup(track),
    };
    assert(report.track);
    VEC_PUSH(on_track_list_changed, report);
}