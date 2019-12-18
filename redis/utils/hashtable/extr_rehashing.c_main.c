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
typedef  int /*<<< orphan*/  dict ;

/* Variables and functions */
 unsigned long MAX1 ; 
 unsigned long MAX2 ; 
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictResize (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictTypeTest ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stressGetKeys (int /*<<< orphan*/ *,int,int*,int*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int main(void) {
    dict *d = dictCreate(&dictTypeTest,NULL);
    unsigned long i;
    srand(time(NULL));

    for (i = 0; i < MAX1; i++) {
        dictAdd(d,(void*)i,NULL);
        show(d);
    }
    printf("Size: %d\n", (int)dictSize(d));

    for (i = 0; i < MAX1; i++) {
        dictDelete(d,(void*)i);
        dictResize(d);
        show(d);
    }
    dictRelease(d);

    d = dictCreate(&dictTypeTest,NULL);

    printf("Stress testing dictGetSomeKeys\n");
    int perfect_run = 0, approx_run = 0;

    for (i = 0; i < MAX2; i++) {
        dictAdd(d,(void*)i,NULL);
        stressGetKeys(d,100,&perfect_run,&approx_run);
    }

    for (i = 0; i < MAX2; i++) {
        dictDelete(d,(void*)i);
        dictResize(d);
        stressGetKeys(d,100,&perfect_run,&approx_run);
    }

    printf("dictGetSomeKey, %d perfect runs, %d approximated runs\n",
        perfect_run, approx_run);

    dictRelease(d);

    printf("TEST PASSED!\n");
    return 0;
}