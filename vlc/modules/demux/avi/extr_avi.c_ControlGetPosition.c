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
typedef  double uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_5__ {scalar_t__ i_length; scalar_t__ i_time; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 double stream_Size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double ControlGetPosition( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if( p_sys->i_length != 0 )
    {
        return (double)p_sys->i_time / (double)p_sys->i_length;
    }
    else if( stream_Size( p_demux->s ) > 0 )
    {
        double i64 = (uint64_t)vlc_stream_Tell( p_demux->s );
        return i64 / stream_Size( p_demux->s );
    }
    return 0.0;
}