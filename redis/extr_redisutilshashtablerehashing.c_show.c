#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rehashidx; int /*<<< orphan*/ * ht; } ;
typedef  TYPE_1__ dict ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  showBuckets (int /*<<< orphan*/ ) ; 

void show(dict *d) {
    int j;
    if (d->rehashidx != -1) {
        printf("rhidx: ");
        for (j = 0; j < d->rehashidx; j++)
            printf(".");
        printf("|\n");
    }
    printf("ht[0]: ");
    showBuckets(d->ht[0]);
    printf("ht[1]: ");
    showBuckets(d->ht[1]);
    printf("\n");
}