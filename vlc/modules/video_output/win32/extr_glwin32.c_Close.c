#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_window_t ;
struct TYPE_10__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_11__ {int /*<<< orphan*/  sys; int /*<<< orphan*/  p_sensors; scalar_t__ vgl; TYPE_3__* gl; } ;
typedef  TYPE_2__ vout_display_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/ * surface; } ;
typedef  TYPE_3__ vlc_gl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CommonWindowClean (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnhookWindowsSensors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_gl_MakeCurrent (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_gl_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_gl_ReleaseCurrent (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_opengl_Delete (scalar_t__) ; 

__attribute__((used)) static void Close(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;
    vlc_gl_t *gl = sys->gl;

    if (gl)
    {
        vout_window_t *surface = gl->surface;
        if (sys->vgl)
        {
            vlc_gl_MakeCurrent (gl);
            vout_display_opengl_Delete(sys->vgl);
            vlc_gl_ReleaseCurrent (gl);
        }
        vlc_gl_Release (gl);
        vlc_object_delete(surface);
    }

    UnhookWindowsSensors(sys->p_sensors);
    CommonWindowClean(VLC_OBJECT(vd), &sys->sys);

    free(sys);
}