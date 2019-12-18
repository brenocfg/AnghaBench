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
struct sway_workspace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  count_tiling_views ; 
 int /*<<< orphan*/  workspace_for_each_container (struct sway_workspace*,int /*<<< orphan*/ ,size_t*) ; 

size_t workspace_num_tiling_views(struct sway_workspace *ws) {
	size_t count = 0;
	workspace_for_each_container(ws, count_tiling_views, &count);
	return count;
}