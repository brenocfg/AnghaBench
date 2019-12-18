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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/ * pic; } ;
struct priv {TYPE_1__ last; } ;
struct TYPE_5__ {struct priv* priv; } ;
typedef  TYPE_2__ opengl_tex_converter_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct priv*) ; 
 int /*<<< orphan*/  vaegl_release_last_pic (TYPE_2__*,struct priv*) ; 

__attribute__((used)) static void
Close(vlc_object_t *obj)
{
    opengl_tex_converter_t *tc = (void *)obj;
    struct priv *priv = tc->priv;

    if (priv->last.pic != NULL)
        vaegl_release_last_pic(tc, priv);

    free(tc->priv);
}