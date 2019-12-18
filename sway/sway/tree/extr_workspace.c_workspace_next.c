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
 struct sway_workspace* workspace_prev_next_impl (struct sway_workspace*,int) ; 

struct sway_workspace *workspace_next(struct sway_workspace *current) {
	return workspace_prev_next_impl(current, 1);
}