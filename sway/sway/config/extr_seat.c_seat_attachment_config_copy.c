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
struct seat_attachment_config {int /*<<< orphan*/  identifier; } ;

/* Variables and functions */
 struct seat_attachment_config* seat_attachment_config_new () ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct seat_attachment_config *seat_attachment_config_copy(
		struct seat_attachment_config *attachment) {
	struct seat_attachment_config *copy = seat_attachment_config_new();
	if (!copy) {
		return NULL;
	}

	copy->identifier = strdup(attachment->identifier);

	return copy;
}