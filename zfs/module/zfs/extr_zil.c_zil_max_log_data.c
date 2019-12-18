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
struct TYPE_3__ {int zl_max_block_size; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int /*<<< orphan*/  zil_chain_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  lr_write_t ;

/* Variables and functions */

uint64_t
zil_max_log_data(zilog_t *zilog)
{
	return (zilog->zl_max_block_size -
	    sizeof (zil_chain_t) - sizeof (lr_write_t));
}