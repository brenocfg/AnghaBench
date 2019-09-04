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
struct TYPE_3__ {int /*<<< orphan*/  pCond; scalar_t__ noError; } ;
typedef  TYPE_1__ cond_t ;

/* Variables and functions */
 int pthread_cond_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int destroyCond(cond_t* cond)
{
    if (cond->noError) {
        int const ret = pthread_cond_destroy(&cond->pCond);
        return ret;
    }
    return 0;
}