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
struct wined3d_vec4 {int /*<<< orphan*/  w; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *debug_vec4(const struct wined3d_vec4 *v)
{
    if (!v)
        return "(null)";
    return wine_dbg_sprintf("{%.8e, %.8e, %.8e, %.8e}",
            v->x, v->y, v->z, v->w);
}