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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  maptype_t ;

/* Variables and functions */
 int /*<<< orphan*/  iterate_through_spacemap_logs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_unflushed_cb ; 

__attribute__((used)) static void
load_unflushed_to_ms_allocatables(spa_t *spa, maptype_t maptype)
{
	iterate_through_spacemap_logs(spa, load_unflushed_cb, &maptype);
}