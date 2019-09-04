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
struct wined3d_box {int /*<<< orphan*/  back; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  front; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;

/* Variables and functions */
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *debug_box(const struct wined3d_box *box)
{
    if (!box)
        return "(null)";
    return wine_dbg_sprintf("(%u, %u, %u)-(%u, %u, %u)",
            box->left, box->top, box->front,
            box->right, box->bottom, box->back);
}