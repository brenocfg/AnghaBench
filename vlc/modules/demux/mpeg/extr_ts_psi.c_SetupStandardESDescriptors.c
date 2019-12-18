#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int i_bitrate; int /*<<< orphan*/  i_cat; } ;
struct TYPE_13__ {TYPE_1__ fmt; } ;
typedef  TYPE_2__ ts_es_t ;
struct TYPE_14__ {TYPE_5__* p_first_descriptor; } ;
typedef  TYPE_3__ dvbpsi_pmt_es_t ;
struct TYPE_15__ {int i_max_bitrate; } ;
typedef  TYPE_4__ dvbpsi_max_bitrate_dr_t ;
struct TYPE_16__ {int i_tag; struct TYPE_16__* p_next; } ;
typedef  TYPE_5__ dvbpsi_descriptor_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  SetupISO639Descriptor (int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*) ; 
 TYPE_4__* dvbpsi_DecodeMaxBitrateDr (TYPE_5__*) ; 

__attribute__((used)) static void SetupStandardESDescriptors( demux_t *p_demux, ts_es_t *p_es,
                                        const dvbpsi_pmt_es_t *p_dvbpsies )
{
    for( dvbpsi_descriptor_t *p_dr = p_dvbpsies->p_first_descriptor;
                              p_dr; p_dr = p_dr->p_next )
    {
        switch( p_dr->i_tag )
        {
            case 0x0a:
                if( p_es->fmt.i_cat == AUDIO_ES )
                    SetupISO639Descriptor( p_demux, p_es, p_dr );
                break;

            case 0x0E:
            {
                dvbpsi_max_bitrate_dr_t *p_btdr = dvbpsi_DecodeMaxBitrateDr( p_dr );
                if( p_btdr && !p_es->fmt.i_bitrate )
                    p_es->fmt.i_bitrate = p_btdr->i_max_bitrate * 50 * 8;
            }
            break;
        }
    }
}