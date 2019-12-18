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
 int N_HTTP_TASK_STATE ; 
 char const** http_task_state_str ; 

const char *
http_task_state_to_str (int state)
{
    if (state < 0 || state >= N_HTTP_TASK_STATE)
        return "unknown";

    return http_task_state_str[state];
}