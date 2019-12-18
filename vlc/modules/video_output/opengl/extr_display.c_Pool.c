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
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  gl; int /*<<< orphan*/  vgl; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  picture_pool_t ;

/* Variables and functions */
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ vlc_gl_MakeCurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_gl_ReleaseCurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vout_display_opengl_GetPool (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static picture_pool_t *Pool (vout_display_t *vd, unsigned count)
{
    vout_display_sys_t *sys = vd->sys;

    if (!sys->pool && vlc_gl_MakeCurrent (sys->gl) == VLC_SUCCESS)
    {
        sys->pool = vout_display_opengl_GetPool (sys->vgl, count);
        vlc_gl_ReleaseCurrent (sys->gl);
    }
    return sys->pool;
}