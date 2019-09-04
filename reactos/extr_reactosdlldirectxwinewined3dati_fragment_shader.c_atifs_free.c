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
struct wined3d_device {struct atifs_private_data* fragment_priv; TYPE_1__* adapter; } ;
struct atifs_private_data {int /*<<< orphan*/  fragment_shaders; } ;
struct TYPE_2__ {int /*<<< orphan*/  gl_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  atifs_free_ffpshader ; 
 int /*<<< orphan*/  heap_free (struct atifs_private_data*) ; 
 int /*<<< orphan*/  wine_rb_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atifs_free(struct wined3d_device *device)
{
    struct atifs_private_data *priv = device->fragment_priv;

    wine_rb_destroy(&priv->fragment_shaders, atifs_free_ffpshader, &device->adapter->gl_info);

    heap_free(priv);
    device->fragment_priv = NULL;
}