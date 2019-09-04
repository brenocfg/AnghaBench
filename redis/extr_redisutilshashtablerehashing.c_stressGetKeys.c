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
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;

/* Variables and functions */
 int dictGetSomeKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int dictSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ ) ; 
 int rand () ; 
 int /*<<< orphan*/  sortPointers ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** zmalloc (int) ; 

void stressGetKeys(dict *d, int times, int *perfect_run, int *approx_run) {
    int j;

    dictEntry **des = zmalloc(sizeof(dictEntry*)*dictSize(d));
    for (j = 0; j < times; j++) {
        int requested = rand() % (dictSize(d)+1);
        int returned = dictGetSomeKeys(d, des, requested);
        int dup = 0;

        qsort(des,returned,sizeof(dictEntry*),sortPointers);
        if (returned > 1) {
            int i;
            for (i = 0; i < returned-1; i++) {
                if (des[i] == des[i+1]) dup++;
            }
        }

        if (requested == returned && dup == 0) {
            (*perfect_run)++;
        } else {
            (*approx_run)++;
            printf("Requested, returned, duplicated: %d %d %d\n",
                requested, returned, dup);
        }
    }
    zfree(des);
}