#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {TYPE_3__* p_b25; TYPE_4__* p_bcas; } ;
typedef  TYPE_2__ stream_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* release ) (TYPE_4__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* release ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static void Close ( vlc_object_t *p_object )
{
    stream_t *p_stream = (stream_t *)p_object;
    stream_sys_t *p_sys = p_stream->p_sys;

    if ( p_sys->p_bcas )
        p_sys->p_bcas->release( p_sys->p_bcas );

    if ( p_sys->p_b25 )
        p_sys->p_b25->release( p_sys->p_b25 );

    free( p_sys );
}