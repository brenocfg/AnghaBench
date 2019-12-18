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
typedef  int uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  obj; TYPE_1__* p_sessions; } ;
typedef  TYPE_2__ cam_t ;
struct TYPE_6__ {int i_slot; } ;

/* Variables and functions */
 int ST_CLOSE_SESSION_REQUEST ; 
 int /*<<< orphan*/  SetWBE (int*,int) ; 
 scalar_t__ TPDURecv (TYPE_2__*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TPDUSend (TYPE_2__*,int,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  T_DATA_LAST ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void SessionSendClose( cam_t *p_cam, int i_session_id )
{
    uint8_t p_response[16];
    uint8_t i_tag;
    uint8_t i_slot = p_cam->p_sessions[i_session_id - 1].i_slot;

    p_response[0] = ST_CLOSE_SESSION_REQUEST;
    p_response[1] = 0x2;
    SetWBE( &p_response[2], i_session_id );

    if ( TPDUSend( p_cam, i_slot, T_DATA_LAST, p_response, 4 ) !=
            VLC_SUCCESS )
    {
        msg_Err( p_cam->obj,
                 "SessionSendClose: couldn't send TPDU on slot %d", i_slot );
        return;
    }
    if ( TPDURecv( p_cam, i_slot, &i_tag, NULL, NULL ) != VLC_SUCCESS )
    {
        msg_Err( p_cam->obj,
                 "SessionSendClose: couldn't recv TPDU on slot %d", i_slot );
        return;
    }
}