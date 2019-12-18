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
struct TYPE_4__ {int /*<<< orphan*/  source; TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_5__ {int /*<<< orphan*/  gl; int /*<<< orphan*/  vgl; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_gl_MakeCurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_gl_ReleaseCurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_display_opengl_Display (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Display(vout_display_t *vd, picture_t *picture)
{
    vout_display_sys_t *sys = vd->sys;
    VLC_UNUSED(picture);

    if (vlc_gl_MakeCurrent (sys->gl) == VLC_SUCCESS)
    {
        vout_display_opengl_Display (sys->vgl, &vd->source);
        vlc_gl_ReleaseCurrent (sys->gl);
    }
}