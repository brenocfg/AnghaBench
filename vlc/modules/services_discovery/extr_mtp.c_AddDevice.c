#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ services_discovery_t ;
struct TYPE_19__ {char* psz_name; scalar_t__ i_count; int /*<<< orphan*/  i_tracks_num; int /*<<< orphan*/ * pp_items; int /*<<< orphan*/  i_product_id; int /*<<< orphan*/  i_dev; int /*<<< orphan*/  i_bus; } ;
typedef  TYPE_3__ services_discovery_sys_t ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_17__ {int /*<<< orphan*/  product_id; } ;
struct TYPE_21__ {TYPE_1__ device_entry; int /*<<< orphan*/  devnum; int /*<<< orphan*/  bus_location; } ;
struct TYPE_20__ {struct TYPE_20__* next; int /*<<< orphan*/  title; int /*<<< orphan*/  artist; } ;
typedef  TYPE_4__ LIBMTP_track_t ;
typedef  TYPE_5__ LIBMTP_raw_device_t ;
typedef  int /*<<< orphan*/  LIBMTP_mtpdevice_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddTrack (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  CountTracks ; 
 char* LIBMTP_Get_Friendlyname (int /*<<< orphan*/ *) ; 
 char* LIBMTP_Get_Modelname (int /*<<< orphan*/ *) ; 
 TYPE_4__* LIBMTP_Get_Tracklisting_With_Callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * LIBMTP_Open_Raw_Device (TYPE_5__*) ; 
 int /*<<< orphan*/  LIBMTP_Release_Device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIBMTP_destroy_track_t (TYPE_4__*) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Info (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AddDevice( services_discovery_t *p_sd,
                      LIBMTP_raw_device_t *p_raw_device )
{
    services_discovery_sys_t *p_sys = p_sd->p_sys;
    char *psz_name = NULL;
    LIBMTP_mtpdevice_t *p_device;
    LIBMTP_track_t *p_track, *p_tmp;

    if( ( p_device = LIBMTP_Open_Raw_Device( p_raw_device ) ) != NULL )
    {
        if( !( psz_name = LIBMTP_Get_Friendlyname( p_device ) ) )
            if( !( psz_name = LIBMTP_Get_Modelname( p_device ) ) )
                if( !( psz_name = strdup( N_( "MTP Device" ) ) ) )
                    return VLC_ENOMEM;
        msg_Info( p_sd, "Found device: %s", psz_name );
        p_sys->i_bus = p_raw_device->bus_location;
        p_sys->i_dev = p_raw_device->devnum;
        p_sys->i_product_id = p_raw_device->device_entry.product_id;
        if( ( p_track = LIBMTP_Get_Tracklisting_With_Callback( p_device,
                            CountTracks, p_sd ) ) == NULL )
        {
            msg_Warn( p_sd, "No tracks on the device" );
            p_sys->pp_items = NULL;
        }
        else
        {
            if( !( p_sys->pp_items = calloc( p_sys->i_tracks_num,
                                                   sizeof( input_item_t * ) ) ) )
            {
                free( psz_name );
                return VLC_ENOMEM;
            }
            p_sys->i_count = 0;
            while( p_track != NULL )
            {
                msg_Dbg( p_sd, "Track found: %s - %s", p_track->artist,
                         p_track->title );
                AddTrack( p_sd, p_track );
                p_tmp = p_track;
                p_track = p_track->next;
                LIBMTP_destroy_track_t( p_tmp );
            }
        }
        p_sys->psz_name = psz_name;
        LIBMTP_Release_Device( p_device );
        return VLC_SUCCESS;
    }
    else
    {
        msg_Info( p_sd, "The device seems to be mounted, unmount it first" );
        return VLC_EGENERIC;
    }
}