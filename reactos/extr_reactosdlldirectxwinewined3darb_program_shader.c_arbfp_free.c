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
struct wined3d_device {struct shader_arb_priv* fragment_priv; int /*<<< orphan*/ * shader_backend; TYPE_1__* adapter; } ;
struct shader_arb_priv {int /*<<< orphan*/  use_arbfp_fixed_func; int /*<<< orphan*/  fragment_shaders; } ;
struct TYPE_2__ {int /*<<< orphan*/  gl_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  arb_program_shader_backend ; 
 int /*<<< orphan*/  arbfp_free_ffpshader ; 
 int /*<<< orphan*/  heap_free (struct shader_arb_priv*) ; 
 int /*<<< orphan*/  wine_rb_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arbfp_free(struct wined3d_device *device)
{
    struct shader_arb_priv *priv = device->fragment_priv;

    wine_rb_destroy(&priv->fragment_shaders, arbfp_free_ffpshader, &device->adapter->gl_info);
    priv->use_arbfp_fixed_func = FALSE;

    if (device->shader_backend != &arb_program_shader_backend)
        heap_free(device->fragment_priv);
}