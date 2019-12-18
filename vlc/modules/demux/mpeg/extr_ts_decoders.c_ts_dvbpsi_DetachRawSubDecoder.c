#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {scalar_t__ p_decoder; } ;
typedef  TYPE_1__ dvbpsi_t ;
typedef  int /*<<< orphan*/  dvbpsi_demux_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_decoder; } ;
typedef  TYPE_2__ dvbpsi_demux_subdec_t ;

/* Variables and functions */
 int /*<<< orphan*/  dvbpsi_DeleteDemuxSubDecoder (TYPE_2__*) ; 
 int /*<<< orphan*/  dvbpsi_DetachDemuxSubDecoder (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* dvbpsi_demuxGetSubDec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ts_dvbpsi_DetachRawSubDecoder( dvbpsi_t *p_dvbpsi, uint8_t i_table_id, uint16_t i_extension )
{
    dvbpsi_demux_t *p_demux = (dvbpsi_demux_t *) p_dvbpsi->p_decoder;

    dvbpsi_demux_subdec_t* p_subdec;
    p_subdec = dvbpsi_demuxGetSubDec( p_demux, i_table_id, i_extension );
    if ( p_subdec == NULL || !p_subdec->p_decoder )
        return;

    dvbpsi_DetachDemuxSubDecoder( p_demux, p_subdec );
    dvbpsi_DeleteDemuxSubDecoder( p_subdec );
}