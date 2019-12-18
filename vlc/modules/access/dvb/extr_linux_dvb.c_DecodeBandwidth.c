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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  fe_bandwidth_t ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_6_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_7_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_8_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_AUTO ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int var_GetInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static fe_bandwidth_t DecodeBandwidth( vlc_object_t *p_access )
{
    fe_bandwidth_t      fe_bandwidth = 0;
    int i_bandwidth = var_GetInteger( p_access, "dvb-bandwidth" );

    msg_Dbg( p_access, "using bandwidth=%d", i_bandwidth );

    switch( i_bandwidth )
    {
        case 0: fe_bandwidth = BANDWIDTH_AUTO; break;
        case 6: fe_bandwidth = BANDWIDTH_6_MHZ; break;
        case 7: fe_bandwidth = BANDWIDTH_7_MHZ; break;
        case 8: fe_bandwidth = BANDWIDTH_8_MHZ; break;
        default:
            msg_Dbg( p_access, "terrestrial dvb has bandwidth not set, using auto" );
            fe_bandwidth = BANDWIDTH_AUTO;
            break;
    }
    return fe_bandwidth;
}