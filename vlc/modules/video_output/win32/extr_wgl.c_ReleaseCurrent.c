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
struct TYPE_4__ {int /*<<< orphan*/  hGLDC; } ;
typedef  TYPE_1__ vout_display_sys_t ;
struct TYPE_5__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ vlc_gl_t ;

/* Variables and functions */
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ReleaseCurrent(vlc_gl_t *gl)
{
    vout_display_sys_t *sys = gl->sys;
    wglMakeCurrent (sys->hGLDC, NULL);
}