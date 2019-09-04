#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seat_config {TYPE_1__* attachments; } ;
struct seat_attachment_config {int /*<<< orphan*/  identifier; } ;
struct TYPE_2__ {int length; struct seat_attachment_config** items; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

struct seat_attachment_config *seat_config_get_attachment(
		struct seat_config *seat_config, char *identifier) {
	for (int i = 0; i < seat_config->attachments->length; ++i) {
		struct seat_attachment_config *attachment =
			seat_config->attachments->items[i];
		if (strcmp(attachment->identifier, identifier) == 0) {
			return attachment;
		}
	}

	return NULL;
}