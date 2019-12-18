#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; scalar_t__* data; } ;
typedef  TYPE_2__ vec_on_state_changed ;
struct TYPE_4__ {TYPE_2__ on_state_changed; } ;
struct ctx {TYPE_1__ report; } ;

/* Variables and functions */
 scalar_t__ VEC_LAST (TYPE_2__*) ; 
 scalar_t__ VLC_PLAYER_STATE_STARTED ; 
 scalar_t__ VLC_PLAYER_STATE_STOPPED ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
test_end_poststop_state(struct ctx *ctx)
{
    vec_on_state_changed *vec = &ctx->report.on_state_changed;
    assert(vec->size > 1);
    assert(vec->data[0] == VLC_PLAYER_STATE_STARTED);
    assert(VEC_LAST(vec) == VLC_PLAYER_STATE_STOPPED);
}