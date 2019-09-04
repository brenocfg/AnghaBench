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
struct wined3d_context {int dummy; } ;
struct wined3d_blitter {TYPE_1__* ops; struct wined3d_blitter* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* blitter_destroy ) (struct wined3d_blitter*,struct wined3d_context*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (struct wined3d_blitter*) ; 
 int /*<<< orphan*/  stub1 (struct wined3d_blitter*,struct wined3d_context*) ; 

__attribute__((used)) static void cpu_blitter_destroy(struct wined3d_blitter *blitter, struct wined3d_context *context)
{
    struct wined3d_blitter *next;

    if ((next = blitter->next))
        next->ops->blitter_destroy(next, context);

    heap_free(blitter);
}