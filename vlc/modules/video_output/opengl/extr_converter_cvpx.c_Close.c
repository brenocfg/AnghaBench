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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct priv {int /*<<< orphan*/ * last_pic; int /*<<< orphan*/  cache; int /*<<< orphan*/ * last_cvtexs; } ;
struct TYPE_2__ {unsigned int tex_count; struct priv* priv; } ;
typedef  TYPE_1__ opengl_tex_converter_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct priv*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Close(vlc_object_t *obj)
{
    opengl_tex_converter_t *tc = (void *)obj;
    struct priv *priv = tc->priv;

#if TARGET_OS_IPHONE
    for (unsigned i = 0; i < tc->tex_count; ++i)
    {
        if (likely(priv->last_cvtexs[i]))
            CFRelease(priv->last_cvtexs[i]);
    }
    CFRelease(priv->cache);
#else
    if (priv->last_pic != NULL)
        picture_Release(priv->last_pic);
#endif
    free(tc->priv);
}