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
struct rfb_softc {int enc_raw_ok; int enc_zlib_ok; int enc_resize_ok; scalar_t__ conn_wait; int /*<<< orphan*/  mtx; int /*<<< orphan*/  cond; int /*<<< orphan*/  sfd; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setname_np (char*) ; 
 scalar_t__ pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfb_handle (struct rfb_softc*,int) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
rfb_thr(void *arg)
{
	struct rfb_softc *rc;
	sigset_t set;

	int cfd;

    pthread_setname_np("rfb");

	rc = arg;

	sigemptyset(&set);
	sigaddset(&set, SIGPIPE);
	if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0) {
		perror("pthread_sigmask");
		return (NULL);
	}

	for (;;) {
		rc->enc_raw_ok = false;
		rc->enc_zlib_ok = false;
		rc->enc_resize_ok = false;

		cfd = accept(rc->sfd, NULL, NULL);
		if (rc->conn_wait) {
			pthread_mutex_lock(&rc->mtx);
			pthread_cond_signal(&rc->cond);
			pthread_mutex_unlock(&rc->mtx);
			rc->conn_wait = 0;
		}
		rfb_handle(rc, cfd);
		close(cfd);
	}

	/* NOTREACHED */
	return (NULL);
}