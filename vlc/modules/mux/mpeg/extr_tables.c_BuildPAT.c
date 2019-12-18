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
struct TYPE_4__ {int /*<<< orphan*/  i_continuity_counter; int /*<<< orphan*/  b_discontinuity; int /*<<< orphan*/  i_pid; } ;
typedef  TYPE_1__ tsmux_stream_t ;
typedef  int /*<<< orphan*/  dvbpsi_t ;
typedef  int /*<<< orphan*/  dvbpsi_psi_section_t ;
typedef  int /*<<< orphan*/  dvbpsi_pat_t ;
typedef  int /*<<< orphan*/  block_t ;
typedef  int /*<<< orphan*/  PEStoTSCallback ;

/* Variables and functions */
 int /*<<< orphan*/  PEStoTS (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WritePSISection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvbpsi_DeletePSISections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvbpsi_pat_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvbpsi_pat_init (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  dvbpsi_pat_program_add (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dvbpsi_pat_sections_generate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ *) ; 

void BuildPAT( dvbpsi_t *p_dvbpsi,
               void *p_opaque, PEStoTSCallback pf_callback,
               int i_tsid, int i_pat_version_number,
               tsmux_stream_t *p_pat,
               unsigned i_programs, tsmux_stream_t *p_pmt, const int *pi_programs_number )
{
    dvbpsi_pat_t         patpsi;
    dvbpsi_psi_section_t *p_section;

    dvbpsi_pat_init( &patpsi, i_tsid, i_pat_version_number, true /* b_current_next */ );
    /* add all programs */
    for (unsigned i = 0; i < i_programs; i++ )
        dvbpsi_pat_program_add( &patpsi, pi_programs_number[i], p_pmt[i].i_pid );

    p_section = dvbpsi_pat_sections_generate( p_dvbpsi, &patpsi, 0 );
    if( likely(p_section) )
    {
        block_t *p_block = WritePSISection( p_section );
        if( likely(p_block) )
        {
            PEStoTS( p_opaque, pf_callback, p_block, p_pat->i_pid,
                     &p_pat->b_discontinuity, &p_pat->i_continuity_counter );
        }
        dvbpsi_DeletePSISections( p_section );
    }
    dvbpsi_pat_empty( &patpsi );
}