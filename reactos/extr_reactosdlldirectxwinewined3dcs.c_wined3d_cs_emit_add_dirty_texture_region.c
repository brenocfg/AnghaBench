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
struct wined3d_texture {int /*<<< orphan*/  resource; } ;
struct wined3d_cs_add_dirty_texture_region {unsigned int layer; struct wined3d_texture* texture; int /*<<< orphan*/  opcode; } ;
struct wined3d_cs {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* submit ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;struct wined3d_cs_add_dirty_texture_region* (* require_space ) (struct wined3d_cs*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_CS_OP_ADD_DIRTY_TEXTURE_REGION ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 struct wined3d_cs_add_dirty_texture_region* stub1 (struct wined3d_cs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_acquire (int /*<<< orphan*/ *) ; 

void wined3d_cs_emit_add_dirty_texture_region(struct wined3d_cs *cs,
        struct wined3d_texture *texture, unsigned int layer)
{
    struct wined3d_cs_add_dirty_texture_region *op;

    op = cs->ops->require_space(cs, sizeof(*op), WINED3D_CS_QUEUE_DEFAULT);
    op->opcode = WINED3D_CS_OP_ADD_DIRTY_TEXTURE_REGION;
    op->texture = texture;
    op->layer = layer;

    wined3d_resource_acquire(&texture->resource);

    cs->ops->submit(cs, WINED3D_CS_QUEUE_DEFAULT);
}