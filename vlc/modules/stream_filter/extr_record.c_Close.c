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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_6__ {scalar_t__ f; } ;
typedef  TYPE_2__ stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Stop (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    stream_t *s = (stream_t*)p_this;
    stream_sys_t *p_sys = s->p_sys;

    if( p_sys->f )
        Stop( s );

    free( p_sys );
}