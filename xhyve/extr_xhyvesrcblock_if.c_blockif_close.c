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
struct blockif_ctxt {int bc_magic; int bc_closing; int /*<<< orphan*/  bc_fd; int /*<<< orphan*/ * bc_btid; int /*<<< orphan*/  bc_cond; int /*<<< orphan*/  bc_mtx; } ;

/* Variables and functions */
 int BLOCKIF_NUMTHR ; 
 scalar_t__ BLOCKIF_SIG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct blockif_ctxt*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
blockif_close(struct blockif_ctxt *bc)
{
	void *jval;
	int err, i;

	err = 0;

	assert(bc->bc_magic == ((int) BLOCKIF_SIG));

	/*
	 * Stop the block i/o thread
	 */
	pthread_mutex_lock(&bc->bc_mtx);
	bc->bc_closing = 1;
	pthread_mutex_unlock(&bc->bc_mtx);
	pthread_cond_broadcast(&bc->bc_cond);
	for (i = 0; i < BLOCKIF_NUMTHR; i++)
		pthread_join(bc->bc_btid[i], &jval);

	/* XXX Cancel queued i/o's ??? */

	/*
	 * Release resources
	 */
	bc->bc_magic = 0;
	close(bc->bc_fd);
	free(bc);

	return (0);
}