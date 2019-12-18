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
struct TYPE_3__ {int i_channel; } ;
typedef  TYPE_1__ eia608_t ;

/* Variables and functions */

__attribute__((used)) static void Eia608ParseChannel( eia608_t *h, const uint8_t d[2] )
{
    /* Check odd parity */
    static const int p4[16] = {
        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0
    };
    if( p4[d[0] & 0xf] == p4[d[0] >> 4] ||
        p4[d[1] & 0xf] == p4[ d[1] >> 4] )
    {
        h->i_channel = -1;
        return;
    }

    /* */
    const int d1 = d[0] & 0x7f;
    if( d1 >= 0x10 && d1 <= 0x1f )
        h->i_channel = 1 + ((d1 & 0x08) != 0);
    else if( d1 < 0x10 )
        h->i_channel = 3;
}