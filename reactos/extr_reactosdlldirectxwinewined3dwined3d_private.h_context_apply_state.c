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
struct wined3d_state {int dummy; } ;
struct wined3d_context {struct StateEntry* state_table; } ;
struct StateEntry {size_t representative; int /*<<< orphan*/  (* apply ) (struct wined3d_context*,struct wined3d_state const*,size_t) ;} ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wined3d_context*,struct wined3d_state const*,size_t) ; 

__attribute__((used)) static inline void context_apply_state(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    const struct StateEntry *state_table = context->state_table;
    DWORD rep = state_table[state_id].representative;
    state_table[rep].apply(context, state, rep);
}