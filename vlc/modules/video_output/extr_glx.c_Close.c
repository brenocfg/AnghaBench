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
typedef  TYPE_1__ vlc_gl_t ;
struct TYPE_6__ {int /*<<< orphan*/  win; int /*<<< orphan*/  ctx; int /*<<< orphan*/ * display; } ;
typedef  TYPE_2__ vlc_gl_sys_t ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  glXDestroyContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXDestroyWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close(vlc_gl_t *gl)
{
    vlc_gl_sys_t *sys = gl->sys;
    Display *dpy = sys->display;

    glXDestroyContext(dpy, sys->ctx);
    glXDestroyWindow(dpy, sys->win);
    XCloseDisplay(dpy);
    free(sys);
}