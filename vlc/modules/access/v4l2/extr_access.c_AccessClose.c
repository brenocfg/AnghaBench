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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  controls; int /*<<< orphan*/  bufc; int /*<<< orphan*/ * bufv; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ControlsDeinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopMmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_parent (int /*<<< orphan*/ *) ; 

void AccessClose( vlc_object_t *obj )
{
    stream_t *access = (stream_t *)obj;
    access_sys_t *sys = access->p_sys;

    if (sys->bufv != NULL)
        StopMmap (sys->fd, sys->bufv, sys->bufc);
    ControlsDeinit(vlc_object_parent(obj), sys->controls);
    v4l2_close (sys->fd);
    free( sys );
}