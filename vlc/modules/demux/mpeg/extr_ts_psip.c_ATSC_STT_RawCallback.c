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
typedef  int /*<<< orphan*/  dvbpsi_t ;
struct TYPE_4__ {struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ dvbpsi_psi_section_t ;
typedef  int /*<<< orphan*/  dvbpsi_atsc_stt_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATSC_STT_Callback (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DVBPlague_STT_Decode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ATSC_STT_RawCallback( dvbpsi_t *p_handle, const dvbpsi_psi_section_t* p_section,
                                  void *p_base_pid )
{
    VLC_UNUSED( p_handle );
    for( ; p_section ; p_section = p_section->p_next )
    {
        dvbpsi_atsc_stt_t *p_stt = DVBPlague_STT_Decode( p_section );
        if( p_stt ) /* Send to real callback */
            ATSC_STT_Callback( p_base_pid, p_stt );
    }
}