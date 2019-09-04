#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data_t ;
struct TYPE_3__ {scalar_t__ use_dictionary; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 int /*<<< orphan*/  data_has_dict (int /*<<< orphan*/  const*) ; 

int config_skip_data(config_t const* config, data_t const* data) {
    return config->use_dictionary && !data_has_dict(data);
}