#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* const table; } ;
typedef  TYPE_1__ memoTable_t ;

/* Variables and functions */
 scalar_t__ ZSTD_STRATEGY_MAX ; 
 int /*<<< orphan*/  free (TYPE_1__* const) ; 

__attribute__((used)) static void freeMemoTableArray(memoTable_t* const mtAll) {
    int i;
    if(mtAll == NULL) { return; }
    for(i = 1; i <= (int)ZSTD_STRATEGY_MAX; i++) {
        free(mtAll[i].table);
    }
    free(mtAll);
}