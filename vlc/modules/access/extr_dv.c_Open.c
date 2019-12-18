#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct raw1394_portinfo {int dummy; } ;
struct TYPE_13__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_12__ {int events; int /*<<< orphan*/  fd; } ;
struct TYPE_14__ {scalar_t__ i_cards; scalar_t__ i_node; int i_channel; TYPE_5__* p_ev; TYPE_1__ raw1394_poll; int /*<<< orphan*/ * p_raw1394; scalar_t__ i_port; int /*<<< orphan*/ * p_avc1394; scalar_t__ i_guid; int /*<<< orphan*/  lock; int /*<<< orphan*/ * p_frame; } ;
typedef  TYPE_3__ access_sys_t ;
struct TYPE_15__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  lock; TYPE_2__* p_access; int /*<<< orphan*/ * p_frame; int /*<<< orphan*/ ** pp_last; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_SET_CALLBACKS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * AVCOpen (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  Block ; 
 int /*<<< orphan*/  Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Control ; 
 scalar_t__ DiscoverAVC (TYPE_2__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  ISOCHRONOUS_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  ISOCHRONOUS_QUEUE_LENGTH ; 
 int POLLIN ; 
 int POLLPRI ; 
 int /*<<< orphan*/  RAW1394_DMA_PACKET_PER_BUFFER ; 
 int /*<<< orphan*/  Raw1394EventThread ; 
 int /*<<< orphan*/  Raw1394Handler ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_OUTPUT ; 
 TYPE_5__* calloc (int,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  raw1394_get_fd (int /*<<< orphan*/ *) ; 
 scalar_t__ raw1394_get_port_info (int /*<<< orphan*/ *,struct raw1394_portinfo*,int) ; 
 scalar_t__ raw1394_iso_recv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw1394_iso_recv_start (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * raw1394_new_handle () ; 
 scalar_t__ raw1394_set_port (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  raw1394_set_userdata (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    stream_t     *p_access = (stream_t*)p_this;
    access_sys_t *p_sys;

    struct raw1394_portinfo port_inf[ 16 ];

    msg_Dbg( p_access, "opening device" );

    /* Set up p_access */
    ACCESS_SET_CALLBACKS( NULL, Block, Control, NULL );

    p_access->p_sys = p_sys = vlc_obj_malloc( p_this, sizeof( *p_sys ) );
    if( !p_sys )
        return VLC_EGENERIC;

    p_sys->i_cards = 0;
    p_sys->i_node = 0;
    p_sys->i_port = 0;
    p_sys->i_guid = 0;
    p_sys->i_channel = 63;
    p_sys->p_raw1394 = NULL;
    p_sys->p_avc1394 = NULL;
    p_sys->p_frame = NULL;
    p_sys->p_ev = NULL;

    vlc_mutex_init( &p_sys->lock );

    p_sys->i_node = DiscoverAVC( p_access, &p_sys->i_port, p_sys->i_guid );
    if( p_sys->i_node < 0 )
    {
        msg_Err( p_access, "failed to open a Firewire (IEEE1394) connection" );
        Close( p_this );
        return VLC_EGENERIC;
    }

    p_sys->p_avc1394 = AVCOpen( p_access, p_sys->i_port );
    if( !p_sys->p_avc1394 )
    {
        msg_Err( p_access, "no Digital Video Control device found" );
        Close( p_this );
        return VLC_EGENERIC;
    }

    p_sys->p_raw1394 = raw1394_new_handle();
    if( !p_sys->p_raw1394 )
    {
        msg_Err( p_access, "no Digital Video device found" );
        Close( p_this );
        return VLC_EGENERIC;
    }

    p_sys->i_cards = raw1394_get_port_info( p_sys->p_raw1394, port_inf, 16 );
    if( p_sys->i_cards < 0 )
    {
        msg_Err( p_access, "failed to get port info" );
        Close( p_this );
        return VLC_EGENERIC;
    }

    if( raw1394_set_port( p_sys->p_raw1394, p_sys->i_port ) < 0 )
    {
        msg_Err( p_access, "failed to set port info" );
        Close( p_this );
        return VLC_EGENERIC;
    }

    if ( raw1394_iso_recv_init( p_sys->p_raw1394, Raw1394Handler,
                ISOCHRONOUS_QUEUE_LENGTH, ISOCHRONOUS_MAX_PACKET_SIZE,
                p_sys->i_channel, RAW1394_DMA_PACKET_PER_BUFFER, -1 ) < 0 )
    {
        msg_Err( p_access, "failed to init isochronous recv" );
        Close( p_this );
        return VLC_EGENERIC;
    }

    raw1394_set_userdata( p_sys->p_raw1394, p_access );
    raw1394_iso_recv_start( p_sys->p_raw1394, -1, -1, 0 );

    p_sys->raw1394_poll.fd = raw1394_get_fd( p_sys->p_raw1394 );
    p_sys->raw1394_poll.events = POLLIN | POLLPRI;

    /* Now create our event thread catcher */
    p_sys->p_ev = calloc( 1, sizeof( *p_sys->p_ev ) );
    if( !p_sys->p_ev )
    {
        msg_Err( p_access, "failed to create event thread struct" );
        Close( p_this );
        return VLC_ENOMEM;
    }

    p_sys->p_ev->p_frame = NULL;
    p_sys->p_ev->pp_last = &p_sys->p_ev->p_frame;
    p_sys->p_ev->p_access = p_access;
    vlc_mutex_init( &p_sys->p_ev->lock );
    if( vlc_clone( &p_sys->p_ev->thread, Raw1394EventThread,
               p_sys->p_ev, VLC_THREAD_PRIORITY_OUTPUT ) )
    {
        msg_Err( p_access, "failed to clone event thread" );
        Close( p_this );
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}