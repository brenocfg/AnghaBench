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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int uint8_t ;
typedef  int int8_t ;
struct TYPE_4__ {int i_pkt_sequence; scalar_t__ i_data; scalar_t__ i_total_data; int* data; int /*<<< orphan*/  i_time; } ;
typedef  TYPE_1__ cea708_demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708_DTVCC_Demux_ServiceBlocks (TYPE_1__*,int /*<<< orphan*/ ,int*,scalar_t__) ; 

void CEA708_DTVCC_Demuxer_Push( cea708_demux_t *h, vlc_tick_t i_start, const uint8_t data[3] )
{
    if( (data[0] & 0x03) == 3 ) /* Header packet */
    {
        const int8_t i_pkt_sequence = data[1] >> 6;

        /* pkt loss/discontinuity, trash buffer */
        if( i_pkt_sequence > 0 && ((h->i_pkt_sequence + 1) % 4) != i_pkt_sequence )
        {
            h->i_data = h->i_total_data = 0;
            h->i_pkt_sequence = i_pkt_sequence;
            return;
        }

        uint8_t pktsize = data[1] & 63;
        if( pktsize == 0 )
            pktsize = 127;
        else
            pktsize = pktsize * 2 - 1;

        h->i_pkt_sequence = i_pkt_sequence;
        h->i_total_data = pktsize;
        h->i_data = 0;
        h->i_time = i_start;
        h->data[h->i_data++] = data[2];
    }
    else if( h->i_total_data > 0 ) /* Not synced to pkt header yet */
    {
        h->data[h->i_data++] = data[1];
        h->data[h->i_data++] = data[2];
    }

    /* pkts assembly finished, we have a service block */
    if( h->i_data > 0 && h->i_data >= h->i_total_data )
    {
        if( h->i_data == h->i_total_data ) /* Only if correct */
            CEA708_DTVCC_Demux_ServiceBlocks( h, h->i_time, h->data, h->i_data );
        h->i_total_data = h->i_data = 0;
    }
}