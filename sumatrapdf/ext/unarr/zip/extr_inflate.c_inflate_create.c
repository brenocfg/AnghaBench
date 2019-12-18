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
struct TYPE_4__ {int inflate64; } ;
typedef  TYPE_1__ inflate_state ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 

inflate_state *inflate_create(bool inflate64)
{
    inflate_state *state = calloc(1, sizeof(inflate_state));
    if (state)
        state->inflate64 = inflate64;
    return state;
}