#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ i_component_tag; } ;
typedef  TYPE_1__ dvbpsi_stream_identifier_dr_t ;
typedef  int /*<<< orphan*/  dvbpsi_pmt_es_t ;
typedef  int /*<<< orphan*/  dvbpsi_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/ * PMTEsFindDescriptor (int /*<<< orphan*/  const*,int) ; 
 TYPE_1__* dvbpsi_DecodeStreamIdentifierDr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool PMTEsHasComponentTagBetween( const dvbpsi_pmt_es_t *p_es,
                                         uint8_t i_low, uint8_t i_high )
{
    dvbpsi_descriptor_t *p_dr = PMTEsFindDescriptor( p_es, 0x52 );
    if( !p_dr )
        return false;
    dvbpsi_stream_identifier_dr_t *p_si = dvbpsi_DecodeStreamIdentifierDr( p_dr );
    if( !p_si )
        return false;

    return p_si->i_component_tag >= i_low && p_si->i_component_tag <= i_high;
}