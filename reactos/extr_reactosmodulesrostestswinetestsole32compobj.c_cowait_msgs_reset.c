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
 scalar_t__ cowait_msgs_first ; 
 scalar_t__ cowait_msgs_last ; 

__attribute__((used)) static void cowait_msgs_reset(void)
{
    cowait_msgs_first = cowait_msgs_last = 0;
}