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
 int IOPRIO_BE_NR ; 

__attribute__((used)) static inline bool ioprio_priority_is_valid(int i) {
        return i >= 0 && i < IOPRIO_BE_NR;
}