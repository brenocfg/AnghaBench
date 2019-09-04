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
struct wined3d_uvec4 {int /*<<< orphan*/  w; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *debug_uvec4(const struct wined3d_uvec4 *v)
{
    if (!v)
        return "(null)";
    return wine_dbg_sprintf("{%u, %u, %u, %u}",
            v->x, v->y, v->z, v->w);
}