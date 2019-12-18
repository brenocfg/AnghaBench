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
struct swaybar_sni {int /*<<< orphan*/  interface; int /*<<< orphan*/  path; int /*<<< orphan*/  service; TYPE_1__* tray; } ;
typedef  int /*<<< orphan*/  sd_bus_slot ;
typedef  int /*<<< orphan*/  sd_bus_message_handler_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int sd_bus_match_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct swaybar_sni*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sni_match_signal(struct swaybar_sni *sni, sd_bus_slot **slot,
		char *signal, sd_bus_message_handler_t callback) {
	int ret = sd_bus_match_signal(sni->tray->bus, slot, sni->service, sni->path,
			sni->interface, signal, callback, sni);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to subscribe to signal %s: %s", signal,
				strerror(-ret));
	}
}