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
struct seat_config {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  merge_seat_config (struct seat_config*,struct seat_config*) ; 
 struct seat_config* new_seat_config (int /*<<< orphan*/ ) ; 

struct seat_config *copy_seat_config(struct seat_config *seat) {
	struct seat_config *copy = new_seat_config(seat->name);
	if (copy == NULL) {
		return NULL;
	}

	merge_seat_config(copy, seat);

	return copy;
}