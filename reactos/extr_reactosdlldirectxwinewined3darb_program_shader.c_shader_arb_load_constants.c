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
struct wined3d_context {int dummy; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  shader_arb_load_constants_internal (void*,struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_ps (struct wined3d_state const*) ; 
 int /*<<< orphan*/  use_vs (struct wined3d_state const*) ; 

__attribute__((used)) static void shader_arb_load_constants(void *shader_priv, struct wined3d_context *context,
        const struct wined3d_state *state)
{
    BOOL vs = use_vs(state);
    BOOL ps = use_ps(state);

    shader_arb_load_constants_internal(shader_priv, context, state, ps, vs, FALSE);
}