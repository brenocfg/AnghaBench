#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int b_discontinuity; int b_current_valid; int /*<<< orphan*/  p_cb_data; int /*<<< orphan*/  (* pf_callback ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ts_dvbpsi_rawtable_decoder_t ;
struct TYPE_14__ {scalar_t__ p_decoder; } ;
typedef  TYPE_2__ dvbpsi_t ;
struct TYPE_15__ {scalar_t__ i_last_number; } ;
typedef  TYPE_3__ dvbpsi_psi_section_t ;
struct TYPE_16__ {int b_discontinuity; } ;
typedef  TYPE_4__ dvbpsi_demux_t ;
struct TYPE_17__ {scalar_t__ i_last_section_number; int /*<<< orphan*/  p_sections; } ;
typedef  TYPE_5__ dvbpsi_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  DVBPSI_DECODER (TYPE_5__*) ; 
 int /*<<< orphan*/  dvbpsi_DeletePSISections (TYPE_3__*) ; 
 int /*<<< orphan*/  dvbpsi_decoder_psi_section_add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ dvbpsi_decoder_psi_sections_completed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbpsi_decoder_reset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ts_dvbpsi_RawSubDecoderGatherSections( dvbpsi_t *p_dvbpsi,
                                                   dvbpsi_decoder_t *p_decoder,
                                                   dvbpsi_psi_section_t * p_section )
{
    dvbpsi_demux_t *p_demux = (dvbpsi_demux_t *) p_dvbpsi->p_decoder;
    ts_dvbpsi_rawtable_decoder_t *p_tabledec = (ts_dvbpsi_rawtable_decoder_t*)p_decoder;
    if ( !p_tabledec )
    {
        dvbpsi_DeletePSISections( p_section );
        return;
    }

    if ( p_demux->b_discontinuity )
    {
        dvbpsi_decoder_reset( DVBPSI_DECODER(p_decoder), true );
        p_tabledec->b_discontinuity = false;
        p_demux->b_discontinuity = false;
    }
    else if( p_decoder->i_last_section_number != p_section->i_last_number )
    {
        dvbpsi_decoder_reset( DVBPSI_DECODER(p_decoder), true );
    }

    /* Add to linked list of sections */
    (void) dvbpsi_decoder_psi_section_add( DVBPSI_DECODER(p_decoder), p_section );
    p_decoder->i_last_section_number = p_section->i_last_number;

    /* Check if we have all the sections */
    if ( dvbpsi_decoder_psi_sections_completed( DVBPSI_DECODER(p_decoder) ) )
    {
        p_tabledec->b_current_valid = true;

        p_tabledec->pf_callback( p_dvbpsi,
                                 p_decoder->p_sections,
                                 p_tabledec->p_cb_data );

        /* Delete sections */
        dvbpsi_decoder_reset( DVBPSI_DECODER(p_decoder), false );
    }
}