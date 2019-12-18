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
struct TYPE_5__ {int /*<<< orphan*/  (* createImageKHR ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {TYPE_1__ egl; } ;
typedef  int /*<<< orphan*/  EGLint ;
typedef  int /*<<< orphan*/  EGLImageKHR ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_DMA_BUF_PLANE0_FD_EXT ; 
 int /*<<< orphan*/  EGL_DMA_BUF_PLANE0_OFFSET_EXT ; 
 int /*<<< orphan*/  EGL_DMA_BUF_PLANE0_PITCH_EXT ; 
 int /*<<< orphan*/  EGL_HEIGHT ; 
 int /*<<< orphan*/  EGL_LINUX_DMA_BUF_EXT ; 
 int /*<<< orphan*/  EGL_LINUX_DRM_FOURCC_EXT ; 
 int /*<<< orphan*/  EGL_NONE ; 
 int /*<<< orphan*/  EGL_WIDTH ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static EGLImageKHR
vaegl_image_create(const opengl_tex_converter_t *tc, EGLint w, EGLint h,
                   EGLint fourcc, EGLint fd, EGLint offset, EGLint pitch)
{
    EGLint attribs[] = {
        EGL_WIDTH, w,
        EGL_HEIGHT, h,
        EGL_LINUX_DRM_FOURCC_EXT, fourcc,
        EGL_DMA_BUF_PLANE0_FD_EXT, fd,
        EGL_DMA_BUF_PLANE0_OFFSET_EXT, offset,
        EGL_DMA_BUF_PLANE0_PITCH_EXT, pitch,
        EGL_NONE
    };

    return tc->gl->egl.createImageKHR(tc->gl, EGL_LINUX_DMA_BUF_EXT, NULL,
                                      attribs);
}