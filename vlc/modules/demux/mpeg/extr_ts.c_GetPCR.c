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
typedef  int uint8_t ;
typedef  int stime_t ;
struct TYPE_3__ {int* p_buffer; int i_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 scalar_t__ likely (int) ; 

__attribute__((used)) static stime_t GetPCR( const block_t *p_pkt )
{
    const uint8_t *p = p_pkt->p_buffer;

    stime_t i_pcr = -1;

    if( likely(p_pkt->i_buffer > 11) &&
        ( p[3]&0x20 ) && /* adaptation */
        ( p[5]&0x10 ) &&
        ( p[4] >= 7 ) )
    {
        /* PCR is 33 bits */
        i_pcr = ( (stime_t)p[6] << 25 ) |
                ( (stime_t)p[7] << 17 ) |
                ( (stime_t)p[8] << 9 ) |
                ( (stime_t)p[9] << 1 ) |
                ( (stime_t)p[10] >> 7 );
    }
    return i_pcr;
}