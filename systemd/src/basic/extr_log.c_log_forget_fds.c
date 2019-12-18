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
 int console_fd ; 
 int journal_fd ; 
 int kmsg_fd ; 
 int syslog_fd ; 

void log_forget_fds(void) {
        /* Do not call from library code. */

        console_fd = kmsg_fd = syslog_fd = journal_fd = -1;
}