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
typedef  scalar_t__ uint32_t ;
struct swaybar_output {int /*<<< orphan*/  bar; } ;
struct swaybar_hotspot {int dummy; } ;
typedef  enum hotspot_event_handling { ____Placeholder_hotspot_event_handling } hotspot_event_handling ;

/* Variables and functions */
 scalar_t__ BTN_LEFT ; 
 int HOTSPOT_IGNORE ; 
 int HOTSPOT_PROCESS ; 
 int /*<<< orphan*/  ipc_send_workspace_command (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static enum hotspot_event_handling workspace_hotspot_callback(
		struct swaybar_output *output, struct swaybar_hotspot *hotspot,
		int x, int y, uint32_t button, void *data) {
	if (button != BTN_LEFT) {
		return HOTSPOT_PROCESS;
	}
	ipc_send_workspace_command(output->bar, (const char *)data);
	return HOTSPOT_IGNORE;
}