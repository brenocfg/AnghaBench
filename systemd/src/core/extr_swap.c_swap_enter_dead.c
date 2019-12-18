#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ result; int /*<<< orphan*/  dynamic_creds; int /*<<< orphan*/  exec_context; int /*<<< orphan*/  exec_runtime; } ;
typedef  scalar_t__ SwapResult ;
typedef  TYPE_1__ Swap ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_DEAD ; 
 int /*<<< orphan*/  SWAP_FAILED ; 
 scalar_t__ SWAP_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dynamic_creds_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_runtime_unref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap_result_to_string (scalar_t__) ; 
 int /*<<< orphan*/  swap_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_destroy_runtime_directory (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_log_result (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_unref_uid_gid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void swap_enter_dead(Swap *s, SwapResult f) {
        assert(s);

        if (s->result == SWAP_SUCCESS)
                s->result = f;

        unit_log_result(UNIT(s), s->result == SWAP_SUCCESS, swap_result_to_string(s->result));
        swap_set_state(s, s->result != SWAP_SUCCESS ? SWAP_FAILED : SWAP_DEAD);

        s->exec_runtime = exec_runtime_unref(s->exec_runtime, true);

        unit_destroy_runtime_directory(UNIT(s), &s->exec_context);

        unit_unref_uid_gid(UNIT(s), true);

        dynamic_creds_destroy(&s->dynamic_creds);
}