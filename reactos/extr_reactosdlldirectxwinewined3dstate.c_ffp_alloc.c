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
struct wined3d_shader_backend_ops {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void *ffp_alloc(const struct wined3d_shader_backend_ops *shader_backend, void *shader_priv)
{
    return shader_priv;
}