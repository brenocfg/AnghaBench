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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_6__ {int b_error; int /*<<< orphan*/  f; } ;
typedef  TYPE_2__ stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t fwrite (int /*<<< orphan*/  const*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

__attribute__((used)) static void Write( stream_t *s, const uint8_t *p_buffer, size_t i_buffer )
{
    stream_sys_t *p_sys = s->p_sys;

    assert( p_sys->f );

    if( i_buffer > 0 )
    {
        const bool b_previous_error = p_sys->b_error;
        const size_t i_written = fwrite( p_buffer, 1, i_buffer, p_sys->f );

        p_sys->b_error = i_written != i_buffer;

        /* TODO maybe a intf_UserError or something like that ? */
        if( p_sys->b_error && !b_previous_error )
            msg_Err( s, "Failed to record data (begin)" );
        else if( !p_sys->b_error && b_previous_error )
            msg_Err( s, "Failed to record data (end)" );
    }
}