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
struct report_vout {int action; int order; int /*<<< orphan*/  es_id; int /*<<< orphan*/  vout; } ;
struct ctx {int dummy; } ;
typedef  enum vlc_vout_order { ____Placeholder_vlc_vout_order } vlc_vout_order ;
typedef  enum vlc_player_vout_action { ____Placeholder_vlc_player_vout_action } vlc_player_vout_action ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_PUSH (int /*<<< orphan*/ ,struct report_vout) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct ctx* get_ctx (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  on_vout_changed ; 
 int /*<<< orphan*/  vlc_es_id_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_Hold (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
player_on_vout_changed(vlc_player_t *player,
                       enum vlc_player_vout_action action,
                       vout_thread_t *vout, enum vlc_vout_order order,
                       vlc_es_id_t *es_id, void *data)
{
    struct ctx *ctx = get_ctx(player, data);
    struct report_vout report = {
        .action = action,
        .vout = vout_Hold(vout),
        .order = order,
        .es_id = vlc_es_id_Hold(es_id),
    };
    assert(report.es_id);
    VEC_PUSH(on_vout_changed, report);
}