#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* gl; } ;
typedef  TYPE_2__ opengl_tex_converter_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* destroyImageKHR ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__ egl; } ;
typedef  int /*<<< orphan*/  EGLImageKHR ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vaegl_image_destroy(const opengl_tex_converter_t *tc, EGLImageKHR image)
{
    tc->gl->egl.destroyImageKHR(tc->gl, image);
}