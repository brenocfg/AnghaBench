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
struct ctx {int /*<<< orphan*/  player; } ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int vlc_player_Start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
player_start(struct ctx *ctx)
{
    int ret = vlc_player_Start(ctx->player);
    assert(ret == VLC_SUCCESS);
}