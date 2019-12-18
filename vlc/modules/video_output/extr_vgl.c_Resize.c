#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int width; unsigned int height; int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* resizeCb ) (int /*<<< orphan*/ ,unsigned int,unsigned int) ;} ;
typedef  TYPE_1__ vout_display_sys_t ;
struct TYPE_7__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ vlc_gl_t ;

/* Variables and functions */
 int /*<<< orphan*/  MakeCurrent (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseCurrent (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void Resize(vlc_gl_t * gl, unsigned w, unsigned h)
{
    vout_display_sys_t *sys = gl->sys;
    if( sys->width == w && sys->height == h )
        return;

    if( !sys->resizeCb )
        return;

    MakeCurrent(gl);
    sys->resizeCb(sys->opaque, w, h);
    ReleaseCurrent(gl);
    sys->width = w;
    sys->height = h;
}