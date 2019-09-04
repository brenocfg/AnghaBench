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
struct logger {int level; } ;

/* Variables and functions */
 struct logger logger ; 

int
log_loggable(int level)
{
    struct logger *l = &logger;

    if (level > l->level) {
        return 0;
    }

    return 1;
}