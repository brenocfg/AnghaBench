#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* (* GetExtensionsStringEXT ) () ;char const* (* GetExtensionsStringARB ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  hGLDC; TYPE_1__ exts; } ;
typedef  TYPE_2__ vout_display_sys_t ;
struct TYPE_7__ {TYPE_2__* sys; } ;
typedef  TYPE_3__ vlc_gl_t ;

/* Variables and functions */
 char const* stub1 () ; 
 char const* stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *GetExtensionsString(vlc_gl_t *gl)
{
    vout_display_sys_t *sys = gl->sys;
    return sys->exts.GetExtensionsStringEXT ?
            sys->exts.GetExtensionsStringEXT() :
            sys->exts.GetExtensionsStringARB(sys->hGLDC);
}