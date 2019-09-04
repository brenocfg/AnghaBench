#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; } ;
struct wined3d_buffer {int modified_areas; TYPE_2__ resource; TYPE_1__* maps; } ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  offset; } ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static BOOL buffer_is_fully_dirty(const struct wined3d_buffer *buffer)
{
    return buffer->modified_areas == 1
            && !buffer->maps->offset && buffer->maps->size == buffer->resource.size;
}