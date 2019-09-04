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
struct bufferchain {scalar_t__ pool_fill; int /*<<< orphan*/ * pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  bc_init (struct bufferchain*) ; 
 int /*<<< orphan*/  bc_poolsize (struct bufferchain*,size_t,size_t) ; 

void bc_prepare(struct bufferchain *bc, size_t pool_size, size_t bufblock)
{
	bc_poolsize(bc, pool_size, bufblock);
	bc->pool = NULL;
	bc->pool_fill = 0;
	bc_init(bc); /* Ensure that members are zeroed for read-only use. */
}