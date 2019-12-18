#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_8__ {scalar_t__ size; } ;
typedef  TYPE_3__ vec_on_capabilities_changed ;
struct TYPE_7__ {scalar_t__ can_seek; scalar_t__ can_pause; } ;
struct TYPE_6__ {TYPE_3__ on_capabilities_changed; } ;
struct ctx {TYPE_2__ params; int /*<<< orphan*/  wait; int /*<<< orphan*/ * player; TYPE_1__ report; } ;
struct TYPE_9__ {int new_caps; } ;

/* Variables and functions */
 TYPE_4__ VEC_LAST (TYPE_3__*) ; 
 int VLC_PLAYER_CAP_PAUSE ; 
 int VLC_PLAYER_CAP_SEEK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ vlc_player_CanPause (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_player_CanSeek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_CondWait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_end_prestop_capabilities(struct ctx *ctx)
{
    vlc_player_t *player = ctx->player;
    vec_on_capabilities_changed *vec = &ctx->report.on_capabilities_changed;
    while (vec->size == 0)
        vlc_player_CondWait(ctx->player, &ctx->wait);
    int new_caps = VEC_LAST(vec).new_caps;
    assert(vlc_player_CanSeek(player) == ctx->params.can_seek
        && !!(new_caps & VLC_PLAYER_CAP_SEEK) == ctx->params.can_seek);
    assert(vlc_player_CanPause(player) == ctx->params.can_pause
        && !!(new_caps & VLC_PLAYER_CAP_PAUSE) == ctx->params.can_pause);
}