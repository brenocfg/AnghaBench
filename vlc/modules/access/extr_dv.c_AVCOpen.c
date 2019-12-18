#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct raw1394_portinfo {int dummy; } ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/ * raw1394handle_t ;
struct TYPE_5__ {int /*<<< orphan*/ * p_avc1394; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVCResetHandler ; 
 int raw1394_get_port_info (int /*<<< orphan*/ *,struct raw1394_portinfo*,int) ; 
 int /*<<< orphan*/ * raw1394_new_handle () ; 
 int /*<<< orphan*/  raw1394_set_bus_reset_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ raw1394_set_port (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static raw1394handle_t AVCOpen( stream_t *p_access, int port )
{
    access_sys_t *p_sys = p_access->p_sys;
    struct raw1394_portinfo pinf[ 16 ];
    int numcards;

    p_sys->p_avc1394 = raw1394_new_handle();
    if( !p_sys->p_avc1394 )
        return NULL;

    numcards = raw1394_get_port_info( p_sys->p_avc1394, pinf, 16 );
    if( numcards < -1 )
        return NULL;
    if( raw1394_set_port( p_sys->p_avc1394, port ) < 0 )
        return NULL;

    raw1394_set_bus_reset_handler( p_sys->p_avc1394, AVCResetHandler );

    return  p_sys->p_avc1394;
}