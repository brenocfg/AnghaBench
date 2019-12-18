#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* display_pics; } ;
struct priv {struct priv* texture_temp_buf; TYPE_1__ pbo; } ;
struct TYPE_5__ {struct priv* priv; } ;
typedef  TYPE_2__ opengl_tex_converter_t ;

/* Variables and functions */
 size_t PBO_DISPLAY_COUNT ; 
 int /*<<< orphan*/  free (struct priv*) ; 
 int /*<<< orphan*/  picture_Release (scalar_t__) ; 

void
opengl_tex_converter_generic_deinit(opengl_tex_converter_t *tc)
{
    struct priv *priv = tc->priv;
    for (size_t i = 0; i < PBO_DISPLAY_COUNT && priv->pbo.display_pics[i]; ++i)
        picture_Release(priv->pbo.display_pics[i]);
    free(priv->texture_temp_buf);
    free(tc->priv);
}