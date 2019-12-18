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
typedef  int /*<<< orphan*/  useconds_t ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct rfb_softc {int cfd; } ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setname_np (char*) ; 
 scalar_t__ rfb_send_screen (struct rfb_softc*,int,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int timeval_delta (struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  usleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
rfb_wr_thr(void *arg)
{
	struct rfb_softc *rc;
	fd_set rfds;
	struct timeval tv;
	struct timeval prev_tv;
	int64_t tdiff;
	int cfd;
	int err;

    pthread_setname_np("rfbout");

	rc = arg;
	cfd = rc->cfd;

	prev_tv.tv_sec = 0;
	prev_tv.tv_usec = 0;
	while (rc->cfd >= 0) {
		FD_ZERO(&rfds);
		FD_SET(cfd, &rfds);
		tv.tv_sec = 0;
		tv.tv_usec = 10000;

		err = select(cfd+1, &rfds, NULL, NULL, &tv);
                if (err < 0)
			return (NULL);

		/* Determine if its time to push screen; ~24hz */
		gettimeofday(&tv, NULL);
		tdiff = timeval_delta(&prev_tv, &tv);
		if (tdiff > 40000) {
			prev_tv.tv_sec = tv.tv_sec;
			prev_tv.tv_usec = tv.tv_usec;
			if (rfb_send_screen(rc, cfd, 0) <= 0) {
				return (NULL);
			}
		} else {
			/* sleep */
			usleep((useconds_t)(40000 - tdiff));
		}
	}

	return (NULL);
}