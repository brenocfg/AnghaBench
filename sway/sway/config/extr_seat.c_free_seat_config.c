#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct seat_config* name; } ;
struct seat_config {TYPE_1__ xcursor_theme; TYPE_2__* attachments; struct seat_config* name; } ;
struct TYPE_4__ {int length; int /*<<< orphan*/ * items; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct seat_config*) ; 
 int /*<<< orphan*/  list_free (TYPE_2__*) ; 
 int /*<<< orphan*/  seat_attachment_config_free (int /*<<< orphan*/ ) ; 

void free_seat_config(struct seat_config *seat) {
	if (!seat) {
		return;
	}

	free(seat->name);
	for (int i = 0; i < seat->attachments->length; ++i) {
		seat_attachment_config_free(seat->attachments->items[i]);
	}
	list_free(seat->attachments);
	free(seat->xcursor_theme.name);
	free(seat);
}