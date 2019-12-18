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
 scalar_t__ COUNT_ALL_PROCESSES ; 
 scalar_t__ COUNT_PIDS ; 
 scalar_t__ arg_count ; 

__attribute__((used)) static const char* counting_what(void) {
        if (arg_count == COUNT_PIDS)
                return "tasks";
        else if (arg_count == COUNT_ALL_PROCESSES)
                return "all processes (incl. kernel)";
        else
                return "userspace processes (excl. kernel)";
}