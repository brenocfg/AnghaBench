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
struct wined3d_unordered_access_view {int dummy; } ;
struct wined3d_cs_set_unordered_access_view {int pipeline; unsigned int view_idx; unsigned int initial_count; struct wined3d_unordered_access_view* view; int /*<<< orphan*/  opcode; } ;
struct wined3d_cs {TYPE_1__* ops; } ;
typedef  enum wined3d_pipeline { ____Placeholder_wined3d_pipeline } wined3d_pipeline ;
struct TYPE_2__ {int /*<<< orphan*/  (* submit ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;struct wined3d_cs_set_unordered_access_view* (* require_space ) (struct wined3d_cs*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_CS_OP_SET_UNORDERED_ACCESS_VIEW ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 struct wined3d_cs_set_unordered_access_view* stub1 (struct wined3d_cs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 

void wined3d_cs_emit_set_unordered_access_view(struct wined3d_cs *cs, enum wined3d_pipeline pipeline,
        unsigned int view_idx, struct wined3d_unordered_access_view *view, unsigned int initial_count)
{
    struct wined3d_cs_set_unordered_access_view *op;

    op = cs->ops->require_space(cs, sizeof(*op), WINED3D_CS_QUEUE_DEFAULT);
    op->opcode = WINED3D_CS_OP_SET_UNORDERED_ACCESS_VIEW;
    op->pipeline = pipeline;
    op->view_idx = view_idx;
    op->view = view;
    op->initial_count = initial_count;

    cs->ops->submit(cs, WINED3D_CS_QUEUE_DEFAULT);
}