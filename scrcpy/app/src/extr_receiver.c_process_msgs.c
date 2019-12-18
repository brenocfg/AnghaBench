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
struct receiver {int dummy; } ;
struct device_msg {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_assert (int) ; 
 int device_msg_deserialize (unsigned char const*,size_t,struct device_msg*) ; 
 int /*<<< orphan*/  device_msg_destroy (struct device_msg*) ; 
 int /*<<< orphan*/  process_msg (struct receiver*,struct device_msg*) ; 

__attribute__((used)) static ssize_t
process_msgs(struct receiver *receiver, const unsigned char *buf, size_t len) {
    size_t head = 0;
    for (;;) {
        struct device_msg msg;
        ssize_t r = device_msg_deserialize(&buf[head], len - head, &msg);
        if (r == -1) {
            return -1;
        }
        if (r == 0) {
            return head;
        }

        process_msg(receiver, &msg);
        device_msg_destroy(&msg);

        head += r;
        SDL_assert(head <= len);
        if (head == len) {
            return head;
        }
    }
}