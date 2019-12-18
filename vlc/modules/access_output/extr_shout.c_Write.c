#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_10__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_11__ {int /*<<< orphan*/  p_shout; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;
struct TYPE_12__ {scalar_t__ i_buffer; int /*<<< orphan*/  p_buffer; struct TYPE_12__* p_next; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 scalar_t__ SHOUTERR_SUCCESS ; 
 size_t VLC_EGENERIC ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_3__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  shout_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shout_get_error (int /*<<< orphan*/ ) ; 
 scalar_t__ shout_open (int /*<<< orphan*/ ) ; 
 scalar_t__ shout_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  shout_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t Write( sout_access_out_t *p_access, block_t *p_buffer )
{
    sout_access_out_sys_t *p_sys = p_access->p_sys;
    size_t i_write = 0;

    shout_sync( p_sys->p_shout );
    while( p_buffer )
    {
        block_t *p_next = p_buffer->p_next;

        if( shout_send( p_sys->p_shout, p_buffer->p_buffer, p_buffer->i_buffer )
             == SHOUTERR_SUCCESS )
        {
            i_write += p_buffer->i_buffer;
        }
        else
        {
            msg_Err( p_access, "cannot write to stream: %s",
                     shout_get_error( p_sys->p_shout ) );

            /* The most common cause seems to be a server disconnect, resulting in a
               Socket Error which can only be fixed by closing and reconnecting.
               Since we already began with a working connection, the most feasable
               approach to get out of this error status is a (timed) reconnect approach. */
            shout_close( p_sys->p_shout );
            msg_Warn( p_access, "server unavailable? trying to reconnect..." );
            /* Re-open the connection (protocol params have already been set) and re-sync */
            if( shout_open( p_sys->p_shout ) == SHOUTERR_SUCCESS )
            {
                shout_sync( p_sys->p_shout );
                msg_Warn( p_access, "reconnected to server" );
            }
            else
            {
                msg_Err( p_access, "failed to reconnect to server" );
                block_ChainRelease( p_buffer );
                return VLC_EGENERIC;
            }

        }
        block_Release( p_buffer );

        /* XXX: Unsure if that's the cause for some audio trouble... */

        p_buffer = p_next;
    }

    return i_write;
}