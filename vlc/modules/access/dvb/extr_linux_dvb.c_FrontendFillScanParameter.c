#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  scan_parameter_t ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_9__ {TYPE_1__ info; } ;
typedef  TYPE_2__ frontend_t ;
struct TYPE_10__ {TYPE_2__* p_frontend; } ;
typedef  TYPE_3__ dvb_sys_t ;

/* Variables and functions */
 scalar_t__ FE_OFDM ; 
 scalar_t__ FE_QAM ; 
 scalar_t__ FE_QPSK ; 
 int ScanParametersDvbC (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ScanParametersDvbS (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ScanParametersDvbT (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

int FrontendFillScanParameter( vlc_object_t *p_access, dvb_sys_t *p_sys, scan_parameter_t *p_scan )
{
    const frontend_t *p_frontend = p_sys->p_frontend;

    if( p_frontend->info.type == FE_OFDM )              /* DVB-T */
        return ScanParametersDvbT( p_access, p_sys, p_scan );
    else if( p_frontend->info.type == FE_QAM )          /* DVB-C */
        return ScanParametersDvbC( p_access, p_sys, p_scan );
    else if( p_frontend->info.type == FE_QPSK )
        return ScanParametersDvbS( p_access, p_sys, p_scan );  /* DVB-S */

    msg_Err( p_access, "frontend scanning not supported" );
    return VLC_EGENERIC;
}