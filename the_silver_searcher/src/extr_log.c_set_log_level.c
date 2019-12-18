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
typedef  enum log_level { ____Placeholder_log_level } log_level ;

/* Variables and functions */
 int log_threshold ; 

void set_log_level(enum log_level threshold) {
    log_threshold = threshold;
}