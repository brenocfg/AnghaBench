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
struct TYPE_7__ {unsigned int tex_count; TYPE_2__* texs; int /*<<< orphan*/  tex_target; TYPE_1__* vt; } ;
typedef  TYPE_3__ opengl_tex_converter_t ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  format; int /*<<< orphan*/  internal; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* TexImage2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tc_common_allocate_textures(const opengl_tex_converter_t *tc, GLuint *textures,
                            const GLsizei *tex_width, const GLsizei *tex_height)
{
    for (unsigned i = 0; i < tc->tex_count; i++)
    {
        tc->vt->BindTexture(tc->tex_target, textures[i]);
        tc->vt->TexImage2D(tc->tex_target, 0, tc->texs[i].internal,
                           tex_width[i], tex_height[i], 0, tc->texs[i].format,
                           tc->texs[i].type, NULL);
    }
    return VLC_SUCCESS;
}