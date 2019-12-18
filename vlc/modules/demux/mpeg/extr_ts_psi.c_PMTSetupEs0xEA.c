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
struct TYPE_3__ {int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ ts_es_t ;
typedef  int /*<<< orphan*/  dvbpsi_pmt_es_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMTEsHasRegistration (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_VC1 ; 
 int /*<<< orphan*/  es_format_Change (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void PMTSetupEs0xEA( demux_t *p_demux, ts_es_t *p_es,
                           const dvbpsi_pmt_es_t *p_dvbpsies )
{
    /* Registration Descriptor */
    if( !PMTEsHasRegistration( p_demux, p_dvbpsies, "VC-1" ) )
    {
        msg_Err( p_demux, "Registration descriptor not found or invalid" );
        return;
    }

    /* registration descriptor for VC-1 (SMPTE rp227) */
    es_format_Change( &p_es->fmt, VIDEO_ES, VLC_CODEC_VC1 );

    /* XXX With Simple and Main profile the SEQUENCE
     * header is modified: video width and height are
     * inserted just after the start code as 2 int16_t
     * The packetizer will take care of that. */
}