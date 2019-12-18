#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  uSTMatrix; } ;
struct priv {int /*<<< orphan*/ * transform_mtx; TYPE_2__ uloc; } ;
struct TYPE_7__ {TYPE_1__* vt; struct priv* priv; } ;
typedef  TYPE_3__ opengl_tex_converter_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* UniformMatrix4fv ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  GLsizei ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tc_anop_prepare_shader(const opengl_tex_converter_t *tc,
                       const GLsizei *tex_width, const GLsizei *tex_height,
                       float alpha)
{
    (void) tex_width; (void) tex_height; (void) alpha;
    struct priv *priv = tc->priv;
    if (priv->transform_mtx != NULL)
        tc->vt->UniformMatrix4fv(priv->uloc.uSTMatrix, 1, GL_FALSE,
                                  priv->transform_mtx);
}