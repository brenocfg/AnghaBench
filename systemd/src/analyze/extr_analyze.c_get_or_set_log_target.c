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
 int get_log_target (int,char**,void*) ; 
 int set_log_target (int,char**,void*) ; 

__attribute__((used)) static int get_or_set_log_target(int argc, char *argv[], void *userdata) {
        return (argc == 1) ? get_log_target(argc, argv, userdata) : set_log_target(argc, argv, userdata);
}