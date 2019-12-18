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
typedef  int /*<<< orphan*/  uint8_t ;
struct blockif_elem {int dummy; } ;
struct blockif_ctxt {int /*<<< orphan*/  bc_mtx; int /*<<< orphan*/  bc_cond; scalar_t__ bc_closing; scalar_t__ bc_isgeom; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPHYS ; 
 int /*<<< orphan*/  blockif_complete (struct blockif_ctxt*,struct blockif_elem*) ; 
 scalar_t__ blockif_dequeue (struct blockif_ctxt*,int /*<<< orphan*/ ,struct blockif_elem**) ; 
 int /*<<< orphan*/  blockif_proc (struct blockif_ctxt*,struct blockif_elem*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 

__attribute__((used)) static void *
blockif_thr(void *arg)
{
	struct blockif_ctxt *bc;
	struct blockif_elem *be;
	pthread_t t;
	uint8_t *buf;

	bc = arg;
	if (bc->bc_isgeom)
		buf = malloc(MAXPHYS);
	else
		buf = NULL;
	t = pthread_self();

	pthread_mutex_lock(&bc->bc_mtx);
	for (;;) {
		while (blockif_dequeue(bc, t, &be)) {
			pthread_mutex_unlock(&bc->bc_mtx);
			blockif_proc(bc, be, buf);
			pthread_mutex_lock(&bc->bc_mtx);
			blockif_complete(bc, be);
		}
		/* Check ctxt status here to see if exit requested */
		if (bc->bc_closing)
			break;
		pthread_cond_wait(&bc->bc_cond, &bc->bc_mtx);
	}
	pthread_mutex_unlock(&bc->bc_mtx);

	if (buf)
		free(buf);
	pthread_exit(NULL);
	return (NULL);
}