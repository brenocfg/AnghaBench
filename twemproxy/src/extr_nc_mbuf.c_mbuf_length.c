#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {scalar_t__ last; scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

uint32_t
mbuf_length(struct mbuf *mbuf)
{
    ASSERT(mbuf->last >= mbuf->pos);

    return (uint32_t)(mbuf->last - mbuf->pos);
}