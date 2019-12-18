#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  glXQueryVersion (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static bool CheckGLX (vlc_object_t *vd, Display *dpy)
{
    int major, minor;
    bool ok = false;

    if (!glXQueryVersion (dpy, &major, &minor))
        msg_Dbg (vd, "GLX extension not available");
    else
    if (major != 1)
        msg_Dbg (vd, "GLX extension version %d.%d unknown", major, minor);
    else
    if (minor < 3)
        msg_Dbg (vd, "GLX extension version %d.%d too old", major, minor);
    else
    {
        msg_Dbg (vd, "using GLX extension version %d.%d", major, minor);
        ok = true;
    }
    return ok;
}