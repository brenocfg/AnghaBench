#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* p_cb_data; int /*<<< orphan*/  pf_callback; int /*<<< orphan*/  pf_gather; } ;
typedef  TYPE_1__ ts_dvbpsi_rawtable_decoder_t ;
typedef  int /*<<< orphan*/  ts_dvbpsi_rawsections_callback_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_decoder; } ;
typedef  TYPE_2__ dvbpsi_t ;

/* Variables and functions */
 int /*<<< orphan*/  DVBPSI_DECODER (TYPE_1__*) ; 
 TYPE_1__* dvbpsi_decoder_new (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  ts_dvbpsi_RawDecoderGatherSections ; 

bool ts_dvbpsi_AttachRawDecoder( dvbpsi_t* p_dvbpsi,
                                 ts_dvbpsi_rawsections_callback_t pf_callback,
                                 void *p_cb_data )
{
    if ( p_dvbpsi->p_decoder )
        return false;

    ts_dvbpsi_rawtable_decoder_t *p_decoder = dvbpsi_decoder_new( NULL, 4096, true, sizeof(*p_decoder) );
    if ( p_decoder == NULL )
        return false;
    p_dvbpsi->p_decoder = DVBPSI_DECODER(p_decoder);

    p_decoder->pf_gather = ts_dvbpsi_RawDecoderGatherSections;
    p_decoder->pf_callback = pf_callback;
    p_decoder->p_cb_data = p_cb_data;

    return true;
}