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
struct TYPE_3__ {int /*<<< orphan*/ * p_first; int /*<<< orphan*/ ** pp_last; scalar_t__ i_depth; } ;
typedef  TYPE_1__ sout_buffer_chain_t ;

/* Variables and functions */

__attribute__((used)) static inline void BufferChainInit  ( sout_buffer_chain_t *c )
{
    c->i_depth = 0;
    c->p_first = NULL;
    c->pp_last = &c->p_first;
}