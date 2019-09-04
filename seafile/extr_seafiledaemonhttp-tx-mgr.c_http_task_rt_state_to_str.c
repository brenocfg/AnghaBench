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
 int N_HTTP_TASK_RT_STATE ; 
 char const** http_task_rt_state_str ; 

const char *
http_task_rt_state_to_str (int rt_state)
{
    if (rt_state < 0 || rt_state >= N_HTTP_TASK_RT_STATE)
        return "unknown";

    return http_task_rt_state_str[rt_state];
}