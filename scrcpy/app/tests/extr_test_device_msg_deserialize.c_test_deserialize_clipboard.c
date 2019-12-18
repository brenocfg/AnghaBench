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
struct TYPE_2__ {int text; } ;
struct device_msg {int type; TYPE_1__ clipboard; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  input ;

/* Variables and functions */
 int DEVICE_MSG_TYPE_CLIPBOARD ; 
 int /*<<< orphan*/  assert (int) ; 
 int device_msg_deserialize (unsigned char const*,int,struct device_msg*) ; 
 int /*<<< orphan*/  device_msg_destroy (struct device_msg*) ; 
 int /*<<< orphan*/  strcmp (char*,int) ; 

__attribute__((used)) static void test_deserialize_clipboard(void) {
    const unsigned char input[] = {
        DEVICE_MSG_TYPE_CLIPBOARD,
        0x00, 0x03, // text length
        0x41, 0x42, 0x43, // "ABC"
    };

    struct device_msg msg;
    ssize_t r = device_msg_deserialize(input, sizeof(input), &msg);
    assert(r == 6);

    assert(msg.type == DEVICE_MSG_TYPE_CLIPBOARD);
    assert(msg.clipboard.text);
    assert(!strcmp("ABC", msg.clipboard.text));

    device_msg_destroy(&msg);
}