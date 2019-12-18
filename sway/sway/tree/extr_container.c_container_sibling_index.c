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
struct sway_container {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_get_siblings (struct sway_container*) ; 
 int list_find (int /*<<< orphan*/ ,struct sway_container*) ; 

int container_sibling_index(struct sway_container *child) {
	return list_find(container_get_siblings(child), child);
}