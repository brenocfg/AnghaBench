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
struct wined3d_context {TYPE_1__* device; } ;
struct shader_arb_priv {struct wined3d_context* last_context; } ;
struct TYPE_2__ {struct shader_arb_priv* shader_priv; } ;

/* Variables and functions */

__attribute__((used)) static void shader_arb_free_context_data(struct wined3d_context *context)
{
    struct shader_arb_priv *priv;

    priv = context->device->shader_priv;
    if (priv->last_context == context)
        priv->last_context = NULL;
}