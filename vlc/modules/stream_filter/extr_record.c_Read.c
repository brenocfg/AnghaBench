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
struct TYPE_5__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_6__ {scalar_t__ f; } ;
typedef  TYPE_2__ stream_sys_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  Write (TYPE_1__*,void*,scalar_t__ const) ; 
 scalar_t__ vlc_stream_Read (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static ssize_t Read( stream_t *s, void *p_read, size_t i_read )
{
    stream_sys_t *p_sys = s->p_sys;
    void *p_record = p_read;
    const ssize_t i_record = vlc_stream_Read( s->s, p_record, i_read );

    /* Dump read data */
    if( p_sys->f )
    {
        if( p_record && i_record > 0 )
            Write( s, p_record, i_record );
    }

    return i_record;
}