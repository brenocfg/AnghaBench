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
struct wined3d_occlusion_query {int /*<<< orphan*/  id; struct wined3d_context* context; int /*<<< orphan*/  entry; } ;
struct wined3d_context {scalar_t__ free_occlusion_query_count; int /*<<< orphan*/ * free_occlusion_queries; int /*<<< orphan*/  free_occlusion_query_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,struct wined3d_context*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_array_reserve (void**,int /*<<< orphan*/ *,scalar_t__,int) ; 

void context_free_occlusion_query(struct wined3d_occlusion_query *query)
{
    struct wined3d_context *context = query->context;

    list_remove(&query->entry);
    query->context = NULL;

    if (!wined3d_array_reserve((void **)&context->free_occlusion_queries,
            &context->free_occlusion_query_size, context->free_occlusion_query_count + 1,
            sizeof(*context->free_occlusion_queries)))
    {
        ERR("Failed to grow free list, leaking query %u in context %p.\n", query->id, context);
        return;
    }

    context->free_occlusion_queries[context->free_occlusion_query_count++] = query->id;
}