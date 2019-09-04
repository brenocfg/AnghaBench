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
struct seat_attachment_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct seat_attachment_config* calloc (int,int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

struct seat_attachment_config *seat_attachment_config_new(void) {
	struct seat_attachment_config *attachment =
		calloc(1, sizeof(struct seat_attachment_config));
	if (!attachment) {
		sway_log(SWAY_DEBUG, "cannot allocate attachment config");
		return NULL;
	}
	return attachment;
}