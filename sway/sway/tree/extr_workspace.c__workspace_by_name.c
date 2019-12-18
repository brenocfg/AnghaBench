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
struct sway_workspace {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static bool _workspace_by_name(struct sway_workspace *ws, void *data) {
	return strcasecmp(ws->name, data) == 0;
}