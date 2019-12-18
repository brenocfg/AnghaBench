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
struct TYPE_6__ {int b_xds; size_t i_class; int i_type; int b_future; TYPE_2__** pkt; } ;
typedef  TYPE_1__ xds_t ;
struct TYPE_7__ {int b_started; scalar_t__ i_data; int i_sum; int* p_data; } ;
typedef  TYPE_2__ xds_packet_t ;
typedef  size_t xds_class_t ;
typedef  int uint8_t ;

/* Variables and functions */
 scalar_t__ XDS_MAX_DATA_SIZE ; 
 int /*<<< orphan*/  XdsDecode (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void XdsParse( xds_t *h, uint8_t d1, uint8_t d2 )
{
    /* TODO check parity */
    d1 &= 0x7f;
    d2 &= 0x7f;

    /* */
    if( d1 >= 0x01 && d1 <= 0x0e )
    {
        const xds_class_t i_class = ( d1 - 1 ) >> 1;
        const int i_type = d2;
        const bool b_start = d1 & 0x01;
        xds_packet_t *pk = &h->pkt[i_class][i_type];

        if( !b_start && !pk->b_started )
        {
            //fprintf( stderr, "xxxxxxxxxxxxxxxXDS Continuying a non started packet, ignoring\n" );
            h->b_xds = false;
            return;
        }

        h->b_xds = true;
        h->i_class = i_class;
        h->i_type  = i_type;
        h->b_future = !b_start;
        pk->b_started = true;
        if( b_start )
        {
            pk->i_data = 0;
            pk->i_sum = d1 + d2;
        }
    }
    else if( d1 == 0x0f && h->b_xds )
    {
        xds_packet_t *pk = &h->pkt[h->i_class][h->i_type];

        /* TODO checksum and decode */
        pk->i_sum += d1 + d2;
        if( pk->i_sum & 0x7f )
        {
            //fprintf( stderr, "xxxxxxxxxxxxxxxXDS invalid checksum, ignoring ---------------------------------\n" );
            pk->b_started = false;
            return;
        }
        if( pk->i_data <= 0 )
        {
            //fprintf( stderr, "xxxxxxxxxxxxxxxXDS empty packet, ignoring ---------------------------------\n" );
            pk->b_started = false;
            return;
        }

        //if( pk->p_data[pk->i_data-1] == 0x40 ) /* Padding byte */
        //    pk->i_data--;
        XdsDecode( h, pk );

        /* Reset it */
        pk->b_started = false;
    }
    else if( d1 >= 0x20 && h->b_xds )
    {
        xds_packet_t *pk = &h->pkt[h->i_class][h->i_type];

        if( pk->i_data+2 > XDS_MAX_DATA_SIZE )
        {
            /* Broken -> reinit */
            //fprintf( stderr, "xxxxxxxxxxxxxxxXDS broken, reset\n" );
            h->b_xds = false;
            pk->b_started = false;
            return;
        }
        /* TODO check parity bit */
        pk->p_data[pk->i_data++] = d1 & 0x7f;
        pk->p_data[pk->i_data++] = d2 & 0x7f;
        pk->i_sum += d1+d2;
    }
    else
    {
        h->b_xds = false;
    }
}