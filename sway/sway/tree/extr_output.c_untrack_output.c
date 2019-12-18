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
struct sway_output {int dummy; } ;
struct sway_container {int /*<<< orphan*/  outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ ,int) ; 
 int list_find (int /*<<< orphan*/ ,struct sway_output*) ; 

__attribute__((used)) static void untrack_output(struct sway_container *con, void *data) {
	struct sway_output *output = data;
	int index = list_find(con->outputs, output);
	if (index != -1) {
		list_del(con->outputs, index);
	}
}