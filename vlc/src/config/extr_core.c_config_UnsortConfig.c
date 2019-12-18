#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_config_t ;
struct TYPE_2__ {scalar_t__ count; int /*<<< orphan*/ ** list; } ;

/* Variables and functions */
 TYPE_1__ config ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 

void config_UnsortConfig (void)
{
    module_config_t **clist;

    clist = config.list;
    config.list = NULL;
    config.count = 0;

    free (clist);
}