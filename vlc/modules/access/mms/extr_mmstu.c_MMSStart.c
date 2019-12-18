#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  i_data; int /*<<< orphan*/  p_data; } ;
typedef  TYPE_1__ var_buffer_t ;
typedef  int uint32_t ;
struct TYPE_16__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_17__ {int i_media_packet_id_type; int i_command; int /*<<< orphan*/  i_command_level; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMS_PACKET_MEDIA ; 
 int /*<<< orphan*/  mms_CommandRead (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mms_CommandSend (TYPE_2__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mms_HeaderMediaRead (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  var_buffer_add32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  var_buffer_add64 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_buffer_add8 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  var_buffer_free (TYPE_1__*) ; 
 int /*<<< orphan*/  var_buffer_initwrite (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int MMSStart( stream_t  *p_access, uint32_t i_packet )
{
    access_sys_t        *p_sys = p_access->p_sys;
    var_buffer_t    buffer;

    /* *** start stream from packet 0 *** */
    var_buffer_initwrite( &buffer, 0 );
    var_buffer_add64( &buffer, 0 ); /* seek point in second */
    var_buffer_add32( &buffer, 0xffffffff );
    var_buffer_add32( &buffer, i_packet ); // begin from start
    var_buffer_add8( &buffer, 0xff ); // stream time limit
    var_buffer_add8( &buffer, 0xff ); //  on 3bytes ...
    var_buffer_add8( &buffer, 0xff ); //
    var_buffer_add8( &buffer, 0x00 ); // don't use limit
    var_buffer_add32( &buffer, p_sys->i_media_packet_id_type );

    mms_CommandSend( p_access, 0x07, p_sys->i_command_level, 0x0001ffff,
                     buffer.p_data, buffer.i_data );

    var_buffer_free( &buffer );

    mms_CommandRead( p_access, 0x05, 0 );

    if( p_sys->i_command != 0x05 )
    {
        msg_Err( p_access,
                 "unknown answer (0x%x instead of 0x05)",
                 p_sys->i_command );
        return -1;
    }
    else
    {
        /* get a packet */
        if( mms_HeaderMediaRead( p_access, MMS_PACKET_MEDIA ) < 0 )
            return -1;
        msg_Dbg( p_access, "streaming started" );
        return 0;
    }
}