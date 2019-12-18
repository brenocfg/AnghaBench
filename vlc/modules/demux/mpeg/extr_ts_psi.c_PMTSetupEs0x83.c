#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ ts_es_t ;
struct TYPE_6__ {int i_program_number; int i_pcr_pid; } ;
typedef  TYPE_2__ dvbpsi_pmt_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_DVD_LPCM ; 
 int /*<<< orphan*/  VLC_CODEC_WIDI_LPCM ; 
 int /*<<< orphan*/  es_format_Change (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PMTSetupEs0x83( const dvbpsi_pmt_t *p_pmt, ts_es_t *p_es, int i_pid )
{
    /* WiDi broadcasts without registration on PMT 0x1, PCR 0x1000 and
     * with audio track pid being 0x1100..0x11FF */
    if ( p_pmt->i_program_number == 0x1 &&
         p_pmt->i_pcr_pid == 0x1000 &&
        ( i_pid >> 8 ) == 0x11 )
    {
        /* Not enough ? might contain 0x83 private descriptor, 2 bytes 0x473F */
        es_format_Change( &p_es->fmt, AUDIO_ES, VLC_CODEC_WIDI_LPCM );
    }
    else
        es_format_Change( &p_es->fmt, AUDIO_ES, VLC_CODEC_DVD_LPCM );
}