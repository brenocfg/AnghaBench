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
 double CHANGE_BY_ONE_THRESHOLD ; 
 double CHANGE_BY_TWO_THRESHOLD ; 

__attribute__((used)) static unsigned convertCompletionToChange(double completion)
{
    if (completion < CHANGE_BY_TWO_THRESHOLD) {
        return 2;
    }
    else if (completion < CHANGE_BY_ONE_THRESHOLD) {
        return 1;
    }
    else {
        return 0;
    }
}