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
struct sway_container {scalar_t__ view; } ;

/* Variables and functions */
 scalar_t__ view_is_urgent (scalar_t__) ; 

__attribute__((used)) static bool find_urgent_iterator(struct sway_container *con, void *data) {
	return con->view && view_is_urgent(con->view);
}