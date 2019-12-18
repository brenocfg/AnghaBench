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
typedef  int /*<<< orphan*/  dvbpsi_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATSC_ATTACH_WITH_FIXED_DECODER (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  ATSC_Detach_Dvbpsi_Decoders (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ATSC_STT_TABLE_ID ; 
 int /*<<< orphan*/  STT ; 

bool ATSC_Attach_Dvbpsi_Base_Decoders( dvbpsi_t *p_handle, void *p_base_pid )
{
    if( !ATSC_ATTACH_WITH_FIXED_DECODER( p_handle, STT, ATSC_STT_TABLE_ID, 0x00, p_base_pid ) )
    {
        ATSC_Detach_Dvbpsi_Decoders( p_handle ); /* shouldn't be any, except demux */
        return false;
    }
    return true;
}