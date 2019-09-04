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
struct controller {int /*<<< orphan*/  video_socket; } ;
struct control_event {int dummy; } ;

/* Variables and functions */
 int SERIALIZED_EVENT_MAX_SIZE ; 
 int control_event_serialize (struct control_event const*,unsigned char*) ; 
 int net_send_all (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static bool
process_event(struct controller *controller,
              const struct control_event *event) {
    unsigned char serialized_event[SERIALIZED_EVENT_MAX_SIZE];
    int length = control_event_serialize(event, serialized_event);
    if (!length) {
        return false;
    }
    int w = net_send_all(controller->video_socket, serialized_event, length);
    return w == length;
}