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
struct sway_container {int /*<<< orphan*/  view; } ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  view_is_urgent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_urgent_iterator(struct sway_container *con, void *data) {
	if (!con->view || !view_is_urgent(con->view)) {
		return;
	}
	list_t *urgent_views = data;
	list_add(urgent_views, con->view);
}