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
struct report_signal {float quality; float strength; } ;
struct ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_PUSH (int /*<<< orphan*/ ,struct report_signal) ; 
 struct ctx* get_ctx (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  on_signal_changed ; 

__attribute__((used)) static void
player_on_signal_changed(vlc_player_t *player,
                         float quality, float strength, void *data)
{
    struct ctx *ctx = get_ctx(player, data);
    struct report_signal report = {
        .quality = quality,
        .strength = strength,
    };
    VEC_PUSH(on_signal_changed, report);
}