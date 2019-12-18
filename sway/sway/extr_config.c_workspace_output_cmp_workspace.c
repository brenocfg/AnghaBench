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
struct workspace_config {int /*<<< orphan*/  workspace; } ;

/* Variables and functions */
 int lenient_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int workspace_output_cmp_workspace(const void *a, const void *b) {
	const struct workspace_config *wsa = a, *wsb = b;
	return lenient_strcmp(wsa->workspace, wsb->workspace);
}