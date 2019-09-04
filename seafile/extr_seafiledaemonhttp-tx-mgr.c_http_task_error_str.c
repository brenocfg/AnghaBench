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
 int N_HTTP_TASK_ERROR ; 
 char const** http_task_error_strs ; 

const char *
http_task_error_str (int task_errno)
{
    if (task_errno < 0 || task_errno >= N_HTTP_TASK_ERROR)
        return "unknown error";

    return http_task_error_strs[task_errno];
}