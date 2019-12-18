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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ts_standards_e ;
struct TYPE_8__ {TYPE_2__* p_first_es; } ;
typedef  TYPE_1__ dvbpsi_pmt_t ;
struct TYPE_9__ {int i_type; struct TYPE_9__* p_next; } ;
typedef  TYPE_2__ dvbpsi_pmt_es_t ;
struct TYPE_10__ {int i_length; int /*<<< orphan*/  p_data; } ;
typedef  TYPE_3__ dvbpsi_descriptor_t ;

/* Variables and functions */
 int GetWBE (int /*<<< orphan*/ ) ; 
 TYPE_3__* PMTEsFindDescriptor (TYPE_2__*,int) ; 
 scalar_t__ PMTEsHasComponentTagBetween (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  TS_STANDARD_ARIB ; 
 int /*<<< orphan*/  TS_STANDARD_AUTO ; 

__attribute__((used)) static ts_standards_e ProbePMTStandard( const dvbpsi_pmt_t *p_dvbpsipmt )
{
    dvbpsi_pmt_es_t *p_dvbpsies;
    for( p_dvbpsies = p_dvbpsipmt->p_first_es; p_dvbpsies; p_dvbpsies = p_dvbpsies->p_next )
    {
        if( p_dvbpsies->i_type == 0x06 )
        {
            /* Probe for ARIB subtitles */
            dvbpsi_descriptor_t *p_dr = PMTEsFindDescriptor( p_dvbpsies, 0xFD );
            if( p_dr && p_dr->i_length >= 2 )
            {
                const uint16_t i_data_component_id = GetWBE(p_dr->p_data);
                if( ( i_data_component_id == 0x0008 &&
                      PMTEsHasComponentTagBetween( p_dvbpsies, 0x30, 0x37 ) ) ||
                    ( i_data_component_id == 0x0012 &&
                      PMTEsHasComponentTagBetween( p_dvbpsies, 0x87, 0x88 ) ) )
                    return TS_STANDARD_ARIB;
            }
        }
    }
    return TS_STANDARD_AUTO;
}