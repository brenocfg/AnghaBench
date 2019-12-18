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
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  job_compare_id ; 
 int /*<<< orphan*/  typesafe_qsort (int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t sort_job_list(Job **list, size_t n) {
        Job *previous = NULL;
        size_t a, b;

        /* Order by numeric IDs */
        typesafe_qsort(list, n, job_compare_id);

        /* Filter out duplicates */
        for (a = 0, b = 0; a < n; a++) {

                if (previous == list[a])
                        continue;

                previous = list[b++] = list[a];
        }

        return b;
}