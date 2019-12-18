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
struct rlimit {int dummy; } ;

/* Variables and functions */
 int _RLIMIT_MAX ; 
 struct rlimit* mfree (struct rlimit*) ; 

void rlimit_free_all(struct rlimit **rl) {
        int i;

        if (!rl)
                return;

        for (i = 0; i < _RLIMIT_MAX; i++)
                rl[i] = mfree(rl[i]);
}