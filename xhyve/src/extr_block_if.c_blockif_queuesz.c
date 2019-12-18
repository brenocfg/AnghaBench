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
struct blockif_ctxt {int bc_magic; } ;

/* Variables and functions */
 int BLOCKIF_MAXREQ ; 
 scalar_t__ BLOCKIF_SIG ; 
 int /*<<< orphan*/  assert (int) ; 

int
blockif_queuesz(struct blockif_ctxt *bc)
{
	assert(bc->bc_magic == ((int) BLOCKIF_SIG));
	return (BLOCKIF_MAXREQ - 1);
}