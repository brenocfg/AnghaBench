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
 int N_CLONE_ERRORS ; 
 char const** error_str ; 

const char *
clone_task_error_to_str (int error)
{
    if (error < 0 || error >= N_CLONE_ERRORS)
        return NULL;
    return error_str[error];
}