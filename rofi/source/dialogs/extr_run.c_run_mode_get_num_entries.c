#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ private_data; } ;
struct TYPE_4__ {unsigned int cmd_list_length; } ;
typedef  TYPE_1__ RunModePrivateData ;
typedef  TYPE_2__ Mode ;

/* Variables and functions */

__attribute__((used)) static unsigned int run_mode_get_num_entries ( const Mode *sw )
{
    const RunModePrivateData *rmpd = (const RunModePrivateData *) sw->private_data;
    return rmpd->cmd_list_length;
}