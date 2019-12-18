#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ i_table_id; scalar_t__ i_extension_id; int /*<<< orphan*/  p_callback_data; int /*<<< orphan*/  (* pf_callback ) (int /*<<< orphan*/ *,size_t,size_t,size_t,size_t,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ts_sections_processor_t ;
struct TYPE_7__ {scalar_t__ p_sys; } ;
typedef  TYPE_2__ dvbpsi_t ;
struct TYPE_8__ {size_t p_payload_end; size_t p_data; scalar_t__ i_table_id; scalar_t__ i_extension; size_t p_payload_start; scalar_t__ b_syntax_indicator; struct TYPE_8__* p_next; } ;
typedef  TYPE_3__ dvbpsi_psi_section_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,size_t,size_t,size_t,size_t,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,size_t,size_t,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ts_subdecoder_rawsection_Callback( dvbpsi_t *p_dvbpsi,
                                               const dvbpsi_psi_section_t* p_section,
                                               void* p_proc_cb_data )
{
    ts_sections_processor_t *p_proc = (ts_sections_processor_t *) p_proc_cb_data;
    if( likely(p_proc->pf_callback) )
    {
        for( const dvbpsi_psi_section_t *p_sec = p_section; p_sec; p_sec = p_sec->p_next )
        {
            size_t i_rawlength = p_sec->p_payload_end - p_sec->p_data;
            if ( p_sec->b_syntax_indicator )
                i_rawlength += 4;

            if( p_proc->i_table_id && p_section->i_table_id != p_proc->i_table_id )
                continue;

            if( p_proc->i_extension_id && p_section->i_extension != p_proc->i_extension_id )
                continue;

            p_proc->pf_callback( (demux_t *) p_dvbpsi->p_sys,
                                 p_sec->p_data, i_rawlength,
                                 p_sec->p_payload_start,
                                 p_sec->p_payload_end - p_sec->p_payload_start,
                                 p_proc->p_callback_data );
        }
    }
}