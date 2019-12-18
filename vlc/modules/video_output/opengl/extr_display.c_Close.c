#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_6__ {int /*<<< orphan*/  vgl; int /*<<< orphan*/ * gl; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vlc_gl_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_gl_MakeCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_gl_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_gl_ReleaseCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_opengl_Delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;
    vlc_gl_t *gl = sys->gl;

    vlc_gl_MakeCurrent (gl);
    vout_display_opengl_Delete (sys->vgl);
    vlc_gl_ReleaseCurrent (gl);

    vlc_gl_Release (gl);
    free (sys);
}