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
struct raw1394_portinfo {int dummy; } ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  raw1394handle_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw1394_destroy_handle (int /*<<< orphan*/ ) ; 
 int raw1394_get_port_info (int /*<<< orphan*/ ,struct raw1394_portinfo*,int) ; 
 int /*<<< orphan*/  raw1394_new_handle () ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Raw1394GetNumPorts( stream_t *p_access )
{
    int n_ports;
    struct raw1394_portinfo pinf[ 16 ];
    raw1394handle_t handle;

    /* get a raw1394 handle */
    if( !( handle = raw1394_new_handle() ) )
    {
        msg_Err( p_access, "raw1394 - failed to get handle: %s",
                 vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    if( ( n_ports = raw1394_get_port_info( handle, pinf, 16 ) ) < 0 )
    {
        msg_Err( p_access, "raw1394 - failed to get port info: %s",
                 vlc_strerror_c(errno) );
        raw1394_destroy_handle( handle );
        return VLC_EGENERIC;
    }
    raw1394_destroy_handle( handle );

    return n_ports;
}