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
struct bufferchain {scalar_t__ pool_fill; scalar_t__ pool_size; struct buffy* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffy_del (struct buffy*) ; 

__attribute__((used)) static void bc_free(struct bufferchain *bc, struct buffy* buf)
{
	if(!buf) return;

	if(bc->pool_fill < bc->pool_size)
	{
		buf->next = bc->pool;
		bc->pool = buf;
		++bc->pool_fill;
	}
	else buffy_del(buf);
}