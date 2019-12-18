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
struct ctx {float rate; int /*<<< orphan*/  player; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_player_ChangeRate (int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void
player_set_rate(struct ctx *ctx, float rate)
{
    vlc_player_ChangeRate(ctx->player, rate);
    ctx->rate = rate;
}