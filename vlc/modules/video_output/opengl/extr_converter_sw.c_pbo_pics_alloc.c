#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ ** display_pics; } ;
struct priv {TYPE_2__ pbo; } ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_9__ {TYPE_1__* vt; struct priv* priv; } ;
typedef  TYPE_3__ opengl_tex_converter_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* BindBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 size_t PBO_DISPLAY_COUNT ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ pbo_data_alloc (TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pbo_picture_create (TYPE_3__ const*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pbo_pics_alloc(const opengl_tex_converter_t *tc)
{
    struct priv *priv = tc->priv;
    for (size_t i = 0; i < PBO_DISPLAY_COUNT; ++i)
    {
        picture_t *pic = priv->pbo.display_pics[i] = pbo_picture_create(tc);
        if (pic == NULL)
            goto error;

        if (pbo_data_alloc(tc, pic) != VLC_SUCCESS)
            goto error;
    }

    /* turn off pbo */
    tc->vt->BindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    return VLC_SUCCESS;
error:
    for (size_t i = 0; i < PBO_DISPLAY_COUNT && priv->pbo.display_pics[i]; ++i)
        picture_Release(priv->pbo.display_pics[i]);
    return VLC_EGENERIC;
}