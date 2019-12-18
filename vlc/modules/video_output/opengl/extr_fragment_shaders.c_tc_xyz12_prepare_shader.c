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
struct TYPE_6__ {int /*<<< orphan*/ * Texture; } ;
struct TYPE_7__ {TYPE_2__ uloc; TYPE_1__* vt; } ;
typedef  TYPE_3__ opengl_tex_converter_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* Uniform1i ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  GLsizei ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tc_xyz12_prepare_shader(const opengl_tex_converter_t *tc,
                        const GLsizei *tex_width, const GLsizei *tex_height,
                        float alpha)
{
    (void) tex_width; (void) tex_height; (void) alpha;
    tc->vt->Uniform1i(tc->uloc.Texture[0], 0);
}