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
struct blockif_req {int dummy; } ;
struct blockif_ctxt {int bc_magic; } ;

/* Variables and functions */
 scalar_t__ BLOCKIF_SIG ; 
 int /*<<< orphan*/  BOP_FLUSH ; 
 int /*<<< orphan*/  assert (int) ; 
 int blockif_request (struct blockif_ctxt*,struct blockif_req*,int /*<<< orphan*/ ) ; 

int
blockif_flush(struct blockif_ctxt *bc, struct blockif_req *breq)
{
	assert(bc->bc_magic == ((int) BLOCKIF_SIG));
	return (blockif_request(bc, breq, BOP_FLUSH));
}