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
struct controller {int /*<<< orphan*/  control_socket; } ;
struct control_msg {int dummy; } ;

/* Variables and functions */
 int CONTROL_MSG_SERIALIZED_MAX_SIZE ; 
 int control_msg_serialize (struct control_msg const*,unsigned char*) ; 
 int net_send_all (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static bool
process_msg(struct controller *controller,
              const struct control_msg *msg) {
    unsigned char serialized_msg[CONTROL_MSG_SERIALIZED_MAX_SIZE];
    int length = control_msg_serialize(msg, serialized_msg);
    if (!length) {
        return false;
    }
    int w = net_send_all(controller->control_socket, serialized_msg, length);
    return w == length;
}