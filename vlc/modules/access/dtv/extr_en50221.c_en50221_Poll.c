#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_12__ {int i_ca_type; scalar_t__ i_next_event; unsigned int i_nb_slots; int* pb_active_slot; int* pb_slot_mmi_expected; int* pb_slot_mmi_undisplayed; scalar_t__ i_timeout; TYPE_1__* p_sessions; int /*<<< orphan*/  obj; scalar_t__* pb_tc_has_data; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ cam_t ;
struct TYPE_13__ {unsigned int num; int flags; } ;
typedef  TYPE_3__ ca_slot_info_t ;
struct TYPE_11__ {unsigned int i_slot; int /*<<< orphan*/  (* pf_manage ) (TYPE_2__*,int) ;scalar_t__ i_resource_id; int /*<<< orphan*/  (* pf_close ) (TYPE_2__*,unsigned int) ;} ;

/* Variables and functions */
#define  CA_CI 129 
#define  CA_CI_LINK 128 
 int CA_CI_MODULE_READY ; 
 int /*<<< orphan*/  CA_GET_SLOT_INFO ; 
 int /*<<< orphan*/  CA_RESET ; 
 scalar_t__* GetLength (scalar_t__*,int*) ; 
 int /*<<< orphan*/  InitSlot (TYPE_2__*,unsigned int) ; 
 unsigned int MAX_SESSIONS ; 
 int MAX_TPDU_SIZE ; 
 int /*<<< orphan*/  SPDUHandle (TYPE_2__*,unsigned int,scalar_t__*,int) ; 
 scalar_t__ TPDURecv (TYPE_2__*,unsigned int,scalar_t__*,scalar_t__*,int*) ; 
 scalar_t__ TPDUSend (TYPE_2__*,unsigned int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ T_DATA_LAST ; 
 scalar_t__ T_RCV ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 scalar_t__ vlc_tick_now () ; 

void en50221_Poll( cam_t * p_cam )
{
    switch( p_cam->i_ca_type )
    {
    case CA_CI_LINK:
        if( vlc_tick_now() > p_cam->i_next_event )
            break;
    case CA_CI:
        return;
    default:
        vlc_assert_unreachable();
    }

    for ( unsigned i_slot = 0; i_slot < p_cam->i_nb_slots; i_slot++ )
    {
        uint8_t i_tag;
        ca_slot_info_t sinfo;

        sinfo.num = i_slot;
        if ( ioctl( p_cam->fd, CA_GET_SLOT_INFO, &sinfo ) != 0 )
        {
            msg_Err( p_cam->obj, "en50221_Poll: couldn't get info on slot %d",
                     i_slot );
            continue;
        }

        if ( !(sinfo.flags & CA_CI_MODULE_READY) )
        {
            if ( p_cam->pb_active_slot[i_slot] )
            {
                msg_Dbg( p_cam->obj, "en50221_Poll: slot %d has been removed",
                         i_slot );
                p_cam->pb_active_slot[i_slot] = false;
                p_cam->pb_slot_mmi_expected[i_slot] = false;
                p_cam->pb_slot_mmi_undisplayed[i_slot] = false;

                /* Close all sessions for this slot. */
                for ( unsigned i = 1; i <= MAX_SESSIONS; i++ )
                {
                    if ( p_cam->p_sessions[i - 1].i_resource_id
                          && p_cam->p_sessions[i - 1].i_slot == i_slot )
                    {
                        if ( p_cam->p_sessions[i - 1].pf_close != NULL )
                        {
                            p_cam->p_sessions[i - 1].pf_close( p_cam, i );
                        }
                        p_cam->p_sessions[i - 1].i_resource_id = 0;
                    }
                }
            }

            continue;
        }
        else if ( !p_cam->pb_active_slot[i_slot] )
        {
            InitSlot( p_cam, i_slot );

            if ( !p_cam->pb_active_slot[i_slot] )
            {
                msg_Dbg( p_cam->obj, "en50221_Poll: resetting slot %d", i_slot );

                if ( ioctl( p_cam->fd, CA_RESET, 1 << i_slot) != 0 )
                {
                    msg_Err( p_cam->obj, "en50221_Poll: couldn't reset slot %d",
                             i_slot );
                }
                continue;
            }

            msg_Dbg( p_cam->obj, "en50221_Poll: slot %d is active",
                     i_slot );
        }

        if ( !p_cam->pb_tc_has_data[i_slot] )
        {
            if ( TPDUSend( p_cam, i_slot, T_DATA_LAST, NULL, 0 ) !=
                    VLC_SUCCESS )
            {
                msg_Err( p_cam->obj,
                         "en50221_Poll: couldn't send TPDU on slot %d",
                         i_slot );
                continue;
            }
            if ( TPDURecv( p_cam, i_slot, &i_tag, NULL, NULL ) !=
                    VLC_SUCCESS )
            {
                msg_Err( p_cam->obj,
                         "en50221_Poll: couldn't recv TPDU on slot %d",
                         i_slot );
                continue;
            }
        }

        while ( p_cam->pb_tc_has_data[i_slot] )
        {
            uint8_t p_tpdu[MAX_TPDU_SIZE];
            int i_size, i_session_size;
            uint8_t *p_session;

            if ( TPDUSend( p_cam, i_slot, T_RCV, NULL, 0 ) != VLC_SUCCESS )
            {
                msg_Err( p_cam->obj,
                         "en50221_Poll: couldn't send TPDU on slot %d",
                         i_slot );
                continue;
            }
            if ( TPDURecv( p_cam, i_slot, &i_tag, p_tpdu, &i_size ) !=
                    VLC_SUCCESS )
            {
                msg_Err( p_cam->obj,
                         "en50221_Poll: couldn't recv TPDU on slot %d",
                         i_slot );
                continue;
            }

            p_session = GetLength( &p_tpdu[3], &i_session_size );
            if ( i_session_size <= 1 )
                continue;

            p_session++;
            i_session_size--;

            if ( i_tag != T_DATA_LAST )
            {
                msg_Err( p_cam->obj,
                         "en50221_Poll: fragmented TPDU not supported" );
                break;
            }

            SPDUHandle( p_cam, i_slot, p_session, i_session_size );
        }
    }

    for ( int i_session_id = 1; i_session_id <= MAX_SESSIONS; i_session_id++ )
    {
        if ( p_cam->p_sessions[i_session_id - 1].i_resource_id
              && p_cam->p_sessions[i_session_id - 1].pf_manage )
        {
            p_cam->p_sessions[i_session_id - 1].pf_manage( p_cam,
                                                           i_session_id );
        }
    }

    p_cam->i_next_event = vlc_tick_now() + p_cam->i_timeout;
}