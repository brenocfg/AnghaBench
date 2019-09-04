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
 int /*<<< orphan*/  _workspace_by_number ; 
 struct sway_workspace* root_find_workspace (int /*<<< orphan*/ ,void*) ; 

struct sway_workspace *workspace_by_number(const char* name) {
	return root_find_workspace(_workspace_by_number, (void *) name);
}