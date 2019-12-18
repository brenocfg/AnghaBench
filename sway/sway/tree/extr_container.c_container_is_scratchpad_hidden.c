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
struct sway_container {int /*<<< orphan*/  workspace; scalar_t__ scratchpad; } ;

/* Variables and functions */

bool container_is_scratchpad_hidden(struct sway_container *con) {
	return con->scratchpad && !con->workspace;
}