#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int i_planes; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_9__ {int /*<<< orphan*/ * buffers; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_3__ picture_sys_t ;
struct TYPE_10__ {TYPE_1__* vt; int /*<<< orphan*/  gl; } ;
typedef  TYPE_4__ opengl_tex_converter_t ;
struct TYPE_7__ {scalar_t__ (* GetError ) () ;int /*<<< orphan*/  (* DeleteBuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* BufferData ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DYNAMIC_DRAW ; 
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 () ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pbo_data_alloc(const opengl_tex_converter_t *tc, picture_t *pic)
{
    picture_sys_t *picsys = pic->p_sys;

    tc->vt->GetError();

    for (int i = 0; i < pic->i_planes; ++i)
    {
        tc->vt->BindBuffer(GL_PIXEL_UNPACK_BUFFER, picsys->buffers[i]);
        tc->vt->BufferData(GL_PIXEL_UNPACK_BUFFER, picsys->bytes[i], NULL,
                            GL_DYNAMIC_DRAW);

        if (tc->vt->GetError() != GL_NO_ERROR)
        {
            msg_Err(tc->gl, "could not alloc PBO buffers");
            tc->vt->DeleteBuffers(i, picsys->buffers);
            return VLC_EGENERIC;
        }
    }
    return VLC_SUCCESS;
}