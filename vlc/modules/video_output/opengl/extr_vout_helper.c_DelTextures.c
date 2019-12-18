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
struct TYPE_5__ {int tex_count; TYPE_1__* vt; } ;
typedef  TYPE_2__ opengl_tex_converter_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* DeleteTextures ) (int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
DelTextures(const opengl_tex_converter_t *tc, GLuint *textures)
{
    tc->vt->DeleteTextures(tc->tex_count, textures);
    memset(textures, 0, tc->tex_count * sizeof(GLuint));
}