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
struct bufferchain {size_t pool_size; size_t bufblock; } ;

/* Variables and functions */

void bc_poolsize(struct bufferchain *bc, size_t pool_size, size_t bufblock)
{
	bc->pool_size = pool_size;
	bc->bufblock = bufblock;
}