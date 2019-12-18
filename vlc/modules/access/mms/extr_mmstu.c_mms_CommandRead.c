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
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {int i_command; int b_eof; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int MMS_RETRY_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int mms_ReceiveCommand (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 

__attribute__((used)) static int mms_CommandRead( stream_t *p_access, int i_command1,
                            int i_command2 )
{
    access_sys_t *p_sys = p_access->p_sys;
    int i_count;
    int i_status;

    for( i_count = 0; i_count < MMS_RETRY_MAX; )
    {
        i_status = mms_ReceiveCommand( p_access );
        if( i_status < 0 || p_sys->i_command == 0 )
        {
            i_count++;
        }
        else if( i_command1 == 0 && i_command2 == 0)
        {
            return VLC_SUCCESS;
        }
        else if( p_sys->i_command == i_command1 ||
                 p_sys->i_command == i_command2 )
        {
            return VLC_SUCCESS;
        }
        else
        {
            switch( p_sys->i_command )
            {
                case 0x03:
                    msg_Warn( p_access, "socket closed by server" );
                    p_sys->b_eof = true;
                    return VLC_EGENERIC;
                case 0x1e:
                    msg_Warn( p_access, "end of media stream" );
                    p_sys->b_eof = true;
                    return VLC_EGENERIC;
                default:
                    break;
            }
        }
    }
    p_sys->b_eof = true;
    msg_Warn( p_access, "failed to receive command (aborting)" );

    return VLC_EGENERIC;
}