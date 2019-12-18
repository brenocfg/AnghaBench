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
struct report_capabilities {int old_caps; int new_caps; } ;
struct ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_PUSH (int /*<<< orphan*/ ,struct report_capabilities) ; 
 struct ctx* get_ctx (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  on_capabilities_changed ; 

__attribute__((used)) static void
player_on_capabilities_changed(vlc_player_t *player, int old_caps, int new_caps,
                               void *data)
{
    struct ctx *ctx = get_ctx(player, data);
    struct report_capabilities report = {
        .old_caps = old_caps,
        .new_caps = new_caps,
    };
    VEC_PUSH(on_capabilities_changed, report);
}