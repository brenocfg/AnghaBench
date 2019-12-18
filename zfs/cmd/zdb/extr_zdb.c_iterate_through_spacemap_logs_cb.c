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
struct TYPE_2__ {int (* uic_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  uic_arg; int /*<<< orphan*/  uic_txg; int /*<<< orphan*/  uic_spa; } ;
typedef  TYPE_1__ unflushed_iter_cb_arg_t ;
typedef  int /*<<< orphan*/  space_map_entry_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iterate_through_spacemap_logs_cb(space_map_entry_t *sme, void *arg)
{
	unflushed_iter_cb_arg_t *uic = arg;
	return (uic->uic_cb(uic->uic_spa, sme, uic->uic_txg, uic->uic_arg));
}