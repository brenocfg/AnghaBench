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
struct TYPE_8__ {int /*<<< orphan*/  texture; int /*<<< orphan*/ * pool; TYPE_1__* prgm; } ;
typedef  TYPE_2__ vout_display_opengl_t ;
typedef  int /*<<< orphan*/  picture_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/ * (* pf_get_pool ) (TYPE_3__*,unsigned int) ;} ;
typedef  TYPE_3__ opengl_tex_converter_t ;
struct TYPE_7__ {TYPE_3__* tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DelTextures (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_ASSERT_NOERROR () ; 
 int /*<<< orphan*/  VLCGL_PICTURE_MAX ; 
 unsigned int __MIN (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_3__*,unsigned int) ; 

picture_pool_t *vout_display_opengl_GetPool(vout_display_opengl_t *vgl, unsigned requested_count)
{
    GL_ASSERT_NOERROR();

    if (vgl->pool)
        return vgl->pool;

    opengl_tex_converter_t *tc = vgl->prgm->tc;
    requested_count = __MIN(VLCGL_PICTURE_MAX, requested_count);
    /* Allocate with tex converter pool callback if it exists */
    assert(tc->pf_get_pool != NULL);
    vgl->pool = tc->pf_get_pool(tc, requested_count);
    if (!vgl->pool)
        goto error;
    return vgl->pool;

error:
    DelTextures(tc, vgl->texture);
    return NULL;
}