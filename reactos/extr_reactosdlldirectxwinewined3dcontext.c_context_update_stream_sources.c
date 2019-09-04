#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {int dummy; } ;
struct wined3d_context {int /*<<< orphan*/  namedArraysLoaded; int /*<<< orphan*/  stream_info; TYPE_1__* d3d_info; scalar_t__ use_immediate_mode_draw; } ;
struct TYPE_2__ {scalar_t__ ffp_generic_attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  context_load_numbered_arrays (struct wined3d_context*,int /*<<< orphan*/ *,struct wined3d_state const*) ; 
 int /*<<< orphan*/  context_load_vertex_data (struct wined3d_context*,int /*<<< orphan*/ *,struct wined3d_state const*) ; 
 int /*<<< orphan*/  context_unload_numbered_arrays (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_unload_vertex_data (struct wined3d_context*) ; 
 scalar_t__ use_vs (struct wined3d_state const*) ; 

void context_update_stream_sources(struct wined3d_context *context, const struct wined3d_state *state)
{

    if (context->use_immediate_mode_draw)
        return;

    context_unload_vertex_data(context);
    if (context->d3d_info->ffp_generic_attributes || use_vs(state))
    {
        TRACE("Loading numbered arrays.\n");
        context_load_numbered_arrays(context, &context->stream_info, state);
        return;
    }

    TRACE("Loading named arrays.\n");
    context_unload_numbered_arrays(context);
    context_load_vertex_data(context, &context->stream_info, state);
    context->namedArraysLoaded = TRUE;
}