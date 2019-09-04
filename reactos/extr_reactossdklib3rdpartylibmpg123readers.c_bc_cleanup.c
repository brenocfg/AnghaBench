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
 int /*<<< orphan*/  buffy_del_chain (int /*<<< orphan*/ *) ; 

void bc_cleanup(struct bufferchain *bc)
{
	buffy_del_chain(bc->pool);
	bc->pool = NULL;
	bc->pool_fill = 0;
}