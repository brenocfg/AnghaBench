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
typedef  TYPE_1__ vlc_gl_t ;
struct TYPE_5__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ vlc_gl_sys_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 char const* eglQueryString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *QueryString(vlc_gl_t *gl, int32_t name)
{
    vlc_gl_sys_t *sys = gl->sys;

    return eglQueryString(sys->display, name);
}