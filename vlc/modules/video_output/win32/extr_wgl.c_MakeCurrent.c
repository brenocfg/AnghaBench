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
struct TYPE_4__ {int /*<<< orphan*/  hGLRC; int /*<<< orphan*/  hGLDC; } ;
typedef  TYPE_1__ vout_display_sys_t ;
struct TYPE_5__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ vlc_gl_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int MakeCurrent(vlc_gl_t *gl)
{
    vout_display_sys_t *sys = gl->sys;
    bool success = wglMakeCurrent(sys->hGLDC, sys->hGLRC);
    return success ? VLC_SUCCESS : VLC_EGENERIC;
}