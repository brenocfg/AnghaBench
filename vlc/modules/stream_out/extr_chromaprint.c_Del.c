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
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_6__ {void* id; } ;
typedef  TYPE_2__ sout_stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Finish (TYPE_1__*) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void Del( sout_stream_t *p_stream, void *id )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    Finish( p_stream );
    if ( p_sys->id == id ) /* not assuming only 1 id is in use.. */
        p_sys->id = NULL;
    free( id );
}