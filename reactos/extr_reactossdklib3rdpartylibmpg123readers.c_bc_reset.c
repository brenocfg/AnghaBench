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
struct buffy {struct buffy* next; } ;
struct bufferchain {struct buffy* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  bc_fill_pool (struct bufferchain*) ; 
 int /*<<< orphan*/  bc_free (struct bufferchain*,struct buffy*) ; 
 int /*<<< orphan*/  bc_init (struct bufferchain*) ; 

__attribute__((used)) static void bc_reset(struct bufferchain *bc)
{
	/* Free current chain, possibly stuffing back into the pool. */
	while(bc->first)
	{
		struct buffy* buf = bc->first;
		bc->first = buf->next;
		bc_free(bc, buf);
	}
	bc_fill_pool(bc); /* Ignoring an error here... */
	bc_init(bc);
}