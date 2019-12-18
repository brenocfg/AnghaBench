#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int i_data; int /*<<< orphan*/  p_data; } ;
typedef  TYPE_1__ var_buffer_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_13__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_14__ {int i_seq_num; int /*<<< orphan*/  lock_netwrite; int /*<<< orphan*/  i_handle_tcp; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int MMS_CMD_HEADERSIZE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int net_Write (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_buffer_add32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  var_buffer_add64 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_buffer_addmemory (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  var_buffer_free (TYPE_1__*) ; 
 int /*<<< orphan*/  var_buffer_initwrite (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mms_CommandSend( stream_t *p_access, int i_command,
                            uint32_t i_prefix1, uint32_t i_prefix2,
                            uint8_t *p_data, int i_data_old )
{
    var_buffer_t buffer;
    access_sys_t *p_sys = p_access->p_sys;
    int i_data_by8, i_ret;
    int i_data = i_data_old;

    while( i_data & 0x7 ) i_data++;
    i_data_by8 = i_data >> 3;

    /* first init buffer */
    var_buffer_initwrite( &buffer, 0 );

    var_buffer_add32( &buffer, 0x00000001 );    /* start sequence */
    var_buffer_add32( &buffer, 0xB00BFACE );
    /* size after protocol type */
    var_buffer_add32( &buffer, i_data + MMS_CMD_HEADERSIZE - 16 );
    var_buffer_add32( &buffer, 0x20534d4d );    /* protocol "MMS " */
    var_buffer_add32( &buffer, i_data_by8 + 4 );
    var_buffer_add32( &buffer, p_sys->i_seq_num ); p_sys->i_seq_num++;
    var_buffer_add64( &buffer, 0 );
    var_buffer_add32( &buffer, i_data_by8 + 2 );
    var_buffer_add32( &buffer, 0x00030000 | i_command ); /* dir | command */
    var_buffer_add32( &buffer, i_prefix1 );    /* command specific */
    var_buffer_add32( &buffer, i_prefix2 );    /* command specific */

    /* specific command data */
    if( p_data && i_data > 0 )
    {
        var_buffer_addmemory( &buffer, p_data, i_data_old );
    }

    /* Append padding to the command data */
    var_buffer_add64( &buffer, 0 );

    /* send it */
    vlc_mutex_lock( &p_sys->lock_netwrite );
    i_ret = net_Write( p_access, p_sys->i_handle_tcp, buffer.p_data,
                       buffer.i_data - ( 8 - ( i_data - i_data_old ) ) );
    vlc_mutex_unlock( &p_sys->lock_netwrite );

    if( i_ret != buffer.i_data - ( 8 - ( i_data - i_data_old ) ) )
    {
        var_buffer_free( &buffer );
        msg_Err( p_access, "failed to send command" );
        return VLC_EGENERIC;
    }

    var_buffer_free( &buffer );
    return VLC_SUCCESS;
}