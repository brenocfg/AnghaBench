#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int available; int bits; } ;
struct TYPE_5__ {TYPE_1__ in; } ;
typedef  TYPE_2__ inflate_state ;

/* Variables and functions */

int inflate_flush(inflate_state *state, unsigned char data_in[8])
{
    int count = 0;
    int keep = state->in.available & 0x7;
    while (count < state->in.available / 8) {
        data_in[count] = (state->in.bits >> (count * 8 + keep)) & 0xFF;
        count++;
    }
    state->in.available = keep;
    return count;
}