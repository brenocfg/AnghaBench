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
struct TYPE_3__ {scalar_t__ p; scalar_t__ p_end; int p_start; } ;
typedef  TYPE_1__ bs_t ;

/* Variables and functions */

__attribute__((used)) static size_t bs_skipeven_bytes_remain( const bs_t *s )
{
    if( s->p )
        return s->p < s->p_end ? (s->p_end - s->p + 1) / 2 - 1: 0;
    else
        return (s->p_end - s->p_start) / 2;
}