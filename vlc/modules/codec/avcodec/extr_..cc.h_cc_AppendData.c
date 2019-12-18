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
struct TYPE_3__ {int i_608channels; int i_708channels; int* p_data; int /*<<< orphan*/  i_data; } ;
typedef  TYPE_1__ cc_data_t ;

/* Variables and functions */

__attribute__((used)) static inline void cc_AppendData( cc_data_t *c, uint8_t cc_preamble, const uint8_t cc[2] )
{
    uint8_t i_field = cc_preamble & 0x03;
    if( i_field == 0 || i_field == 1 )
        c->i_608channels |= (3 << (2 * i_field));
    else
        c->i_708channels |= 1;

    c->p_data[c->i_data++] = cc_preamble;
    c->p_data[c->i_data++] = cc[0];
    c->p_data[c->i_data++] = cc[1];
}