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
 int PRIO_MAX ; 
 int PRIO_MIN ; 

__attribute__((used)) static inline bool nice_is_valid(int n) {
        return n >= PRIO_MIN && n < PRIO_MAX;
}