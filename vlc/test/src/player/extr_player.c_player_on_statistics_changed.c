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
struct input_stats_t {int dummy; } ;
struct ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_PUSH (int /*<<< orphan*/ ,struct input_stats_t) ; 
 struct ctx* get_ctx (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  on_statistics_changed ; 

__attribute__((used)) static void
player_on_statistics_changed(vlc_player_t *player,
                        const struct input_stats_t *stats, void *data)
{
    struct ctx *ctx = get_ctx(player, data);
    struct input_stats_t dup = *stats;
    VEC_PUSH(on_statistics_changed, dup);
}