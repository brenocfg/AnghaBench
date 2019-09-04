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

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 unsigned long* malloc (size_t) ; 
 int /*<<< orphan*/  memtest_test (unsigned long*,size_t,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void memtest_alloc_and_test(size_t megabytes, int passes) {
    size_t bytes = megabytes*1024*1024;
    unsigned long *m = malloc(bytes);

    if (m == NULL) {
        fprintf(stderr,"Unable to allocate %zu megabytes: %s",
            megabytes, strerror(errno));
        exit(1);
    }
    memtest_test(m,bytes,passes,1);
    free(m);
}