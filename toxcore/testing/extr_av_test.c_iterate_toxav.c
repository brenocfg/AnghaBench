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
struct toxav_thread_data {int sig; int /*<<< orphan*/  BobAV; int /*<<< orphan*/  AliceAV; } ;

/* Variables and functions */
 int /*<<< orphan*/  CV_WINDOW_AUTOSIZE ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_sleep (int) ; 
 int /*<<< orphan*/  cvDestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvNamedWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvWaitKey (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  toxav_iterate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toxav_iteration_interval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdout ; 

void *iterate_toxav (void *data)
{
    struct toxav_thread_data *data_cast = data;
#if defined TEST_TRANSFER_V && TEST_TRANSFER_V == 1
    cvNamedWindow(vdout, CV_WINDOW_AUTOSIZE);
#endif

    while (data_cast->sig == 0) {
        toxav_iterate(data_cast->AliceAV);
        toxav_iterate(data_cast->BobAV);
        int rc = MIN(toxav_iteration_interval(data_cast->AliceAV), toxav_iteration_interval(data_cast->BobAV));

        printf("\rIteration interval: %d            ", rc);
        fflush(stdout);

#if defined TEST_TRANSFER_V && TEST_TRANSFER_V == 1

        if (!rc)
            rc = 1;

        cvWaitKey(rc);
#else
        c_sleep(rc);
#endif
    }

    data_cast->sig = 1;

#if defined TEST_TRANSFER_V && TEST_TRANSFER_V == 1
    cvDestroyWindow(vdout);
#endif

    pthread_exit(NULL);
}