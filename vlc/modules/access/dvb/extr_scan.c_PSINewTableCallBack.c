#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_obj; } ;
typedef  TYPE_1__ scan_session_t ;
typedef  int /*<<< orphan*/  dvbpsi_t ;
typedef  int /*<<< orphan*/  dvbpsi_sdt_callback ;
typedef  int /*<<< orphan*/  dvbpsi_nit_callback ;

/* Variables and functions */
 scalar_t__ NITCallBack ; 
 scalar_t__ NIT_CURRENT_NETWORK_TABLE_ID ; 
 scalar_t__ NIT_OTHER_NETWORK_TABLE_ID ; 
 scalar_t__ SDTCallBack ; 
 scalar_t__ SDT_CURRENT_TS_TABLE_ID ; 
 scalar_t__ SDT_OTHER_TS_TABLE_ID ; 
 int /*<<< orphan*/  dvbpsi_nit_attach (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dvbpsi_sdt_attach (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void PSINewTableCallBack( dvbpsi_t *h, uint8_t i_table_id, uint16_t i_extension, void *p_data )
{
    scan_session_t *p_session = (scan_session_t *)p_data;

    if( i_table_id == SDT_CURRENT_TS_TABLE_ID || i_table_id == SDT_OTHER_TS_TABLE_ID )
    {
        if( !dvbpsi_sdt_attach( h, i_table_id, i_extension, (dvbpsi_sdt_callback)SDTCallBack, p_session ) )
            msg_Err( p_session->p_obj, "PSINewTableCallback: failed attaching SDTCallback" );
    }
    else if( i_table_id == NIT_CURRENT_NETWORK_TABLE_ID || i_table_id == NIT_OTHER_NETWORK_TABLE_ID )
    {
        if( !dvbpsi_nit_attach( h, i_table_id, i_extension, (dvbpsi_nit_callback)NITCallBack, p_session ) )
            msg_Err( p_session->p_obj, "PSINewTableCallback: failed attaching NITCallback" );
    }
}