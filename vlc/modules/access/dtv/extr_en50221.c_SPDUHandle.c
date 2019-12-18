#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  obj; TYPE_1__* p_sessions; } ;
typedef  TYPE_2__ cam_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_resource_id; int /*<<< orphan*/  (* pf_close ) (TYPE_2__*,int) ;int /*<<< orphan*/  (* pf_handle ) (TYPE_2__*,int,int*,int) ;} ;

/* Variables and functions */
#define  ST_CLOSE_SESSION_REQUEST 132 
#define  ST_CLOSE_SESSION_RESPONSE 131 
#define  ST_CREATE_SESSION_RESPONSE 130 
#define  ST_OPEN_SESSION_REQUEST 129 
#define  ST_SESSION_NUMBER 128 
 int /*<<< orphan*/  SessionClose (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SessionCreateResponse (TYPE_2__*,int,int*,int) ; 
 int /*<<< orphan*/  SessionOpen (TYPE_2__*,int,int*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 

__attribute__((used)) static void SPDUHandle( cam_t * p_cam, uint8_t i_slot,
                        uint8_t *p_spdu, int i_size )
{
    int i_session_id;

    switch ( p_spdu[0] )
    {
    case ST_SESSION_NUMBER:
        if ( i_size <= 4 )
            return;
        i_session_id = ((int)p_spdu[2] << 8) | p_spdu[3];
        p_cam->p_sessions[i_session_id - 1].pf_handle( p_cam, i_session_id,
                                                       p_spdu + 4, i_size - 4 );
        break;

    case ST_OPEN_SESSION_REQUEST:
        if ( i_size != 6 || p_spdu[1] != 0x4 )
            return;
        SessionOpen( p_cam, i_slot, p_spdu, i_size );
        break;

    case ST_CREATE_SESSION_RESPONSE:
        if ( i_size != 9 || p_spdu[1] != 0x7 )
            return;
        SessionCreateResponse( p_cam, i_slot, p_spdu, i_size );
        break;

    case ST_CLOSE_SESSION_REQUEST:
        if ( i_size != 4 || p_spdu[1] != 0x2 )
            return;
        i_session_id = ((int)p_spdu[2] << 8) | p_spdu[3];
        SessionClose( p_cam, i_session_id );
        break;

    case ST_CLOSE_SESSION_RESPONSE:
        if ( i_size != 5 || p_spdu[1] != 0x3 )
            return;
        i_session_id = ((int)p_spdu[3] << 8) | p_spdu[4];
        if ( p_spdu[2] )
        {
            msg_Err( p_cam->obj,
                     "closing a session which is not allocated (%d)",
                     i_session_id );
        }
        else
        {
            if ( p_cam->p_sessions[i_session_id - 1].pf_close != NULL )
                p_cam->p_sessions[i_session_id - 1].pf_close( p_cam,
                                                              i_session_id );
            p_cam->p_sessions[i_session_id - 1].i_resource_id = 0;
        }
        break;

    default:
        msg_Err( p_cam->obj, "unexpected tag in SPDUHandle (%x)", p_spdu[0] );
        break;
    }
}