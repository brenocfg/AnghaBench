#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_7__ {int i_socket; int /*<<< orphan*/  b_quiet; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTF_IDLE_SLEEP ; 
 int MAX_LINE_LENGTH ; 
 int ReadWin32 (TYPE_2__*,unsigned char*,int*) ; 
 int /*<<< orphan*/  libvlc_Quit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 scalar_t__ net_Read (TYPE_2__*,int,char*,int) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ReadCommand(intf_thread_t *p_intf, char *p_buffer, int *pi_size)
{
#if defined(_WIN32) && !VLC_WINSTORE_APP
    if( p_intf->p_sys->i_socket == -1 && !p_intf->p_sys->b_quiet )
        return ReadWin32( p_intf, (unsigned char*)p_buffer, pi_size );
    else if( p_intf->p_sys->i_socket == -1 )
    {
        vlc_tick_sleep( INTF_IDLE_SLEEP );
        return false;
    }
#endif

    while( *pi_size < MAX_LINE_LENGTH )
    {
        if( p_intf->p_sys->i_socket == -1 )
        {
            if( read( 0/*STDIN_FILENO*/, p_buffer + *pi_size, 1 ) <= 0 )
            {   /* Standard input closed: exit */
                libvlc_Quit( vlc_object_instance(p_intf) );
                p_buffer[*pi_size] = 0;
                return true;
            }
        }
        else
        {   /* Connection closed */
            if( net_Read( p_intf, p_intf->p_sys->i_socket, p_buffer + *pi_size,
                          1 ) <= 0 )
            {
                net_Close( p_intf->p_sys->i_socket );
                p_intf->p_sys->i_socket = -1;
                p_buffer[*pi_size] = 0;
                return true;
            }
        }

        if( p_buffer[ *pi_size ] == '\r' || p_buffer[ *pi_size ] == '\n' )
            break;

        (*pi_size)++;
    }

    if( *pi_size == MAX_LINE_LENGTH ||
        p_buffer[ *pi_size ] == '\r' || p_buffer[ *pi_size ] == '\n' )
    {
        p_buffer[ *pi_size ] = 0;
        return true;
    }

    return false;
}