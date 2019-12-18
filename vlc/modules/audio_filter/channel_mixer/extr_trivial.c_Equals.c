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
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */

__attribute__((used)) static block_t *Equals( filter_t *p_filter, block_t *p_buf )
{
    (void) p_filter;
    return p_buf;
}