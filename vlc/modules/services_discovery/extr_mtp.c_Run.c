#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  services_discovery_t ;
typedef  int /*<<< orphan*/  LIBMTP_raw_device_t ;

/* Variables and functions */
 scalar_t__ AddDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseDevice (int /*<<< orphan*/ *) ; 
 int LIBMTP_Detect_Raw_Devices (int /*<<< orphan*/ **,int*) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *Run( void *data )
{
    LIBMTP_raw_device_t *p_rawdevices;
    int i_numrawdevices;
    int i_ret;
    int i_status = 0;
    services_discovery_t *p_sd = data;

    for(;;)
    {
        int canc = vlc_savecancel();
        i_ret = LIBMTP_Detect_Raw_Devices( &p_rawdevices, &i_numrawdevices );
        if ( i_ret == 0 && i_numrawdevices > 0 && p_rawdevices != NULL &&
             i_status == 0 )
        {
            /* Found a new device, add it */
            msg_Dbg( p_sd, "New device found" );
            if( AddDevice( p_sd, &p_rawdevices[0] ) == VLC_SUCCESS )
                i_status = 1;
            else
                i_status = 2;
        }
        else
        {
            if ( ( i_ret != 0 || i_numrawdevices == 0 || p_rawdevices == NULL )
                 && i_status == 1)
            {
                /* The device is not connected anymore, delete it */
                msg_Info( p_sd, "Device disconnected" );
                CloseDevice( p_sd );
                i_status = 0;
            }
        }
        free( p_rawdevices );
        vlc_restorecancel(canc);
        if( i_status == 2 )
        {
            vlc_tick_sleep( VLC_TICK_FROM_SEC(5) );
            i_status = 0;
        }
        else
            vlc_tick_sleep( VLC_TICK_FROM_MS(500) );
    }
    return NULL;
}