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

/* Variables and functions */

__attribute__((used)) static void shader_none_select_compute(void *shader_priv, struct wined3d_context *context,
        const struct wined3d_state *state) {}