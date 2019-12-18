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
struct control_msg {unsigned char const type; } ;
typedef  int /*<<< orphan*/  expected ;

/* Variables and functions */
 int CONTROL_MSG_SERIALIZED_MAX_SIZE ; 
 unsigned char const CONTROL_MSG_TYPE_BACK_OR_SCREEN_ON ; 
 int /*<<< orphan*/  assert (int) ; 
 int control_msg_serialize (struct control_msg*,unsigned char*) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static void test_serialize_back_or_screen_on(void) {
    struct control_msg msg = {
        .type = CONTROL_MSG_TYPE_BACK_OR_SCREEN_ON,
    };

    unsigned char buf[CONTROL_MSG_SERIALIZED_MAX_SIZE];
    int size = control_msg_serialize(&msg, buf);
    assert(size == 1);

    const unsigned char expected[] = {
        CONTROL_MSG_TYPE_BACK_OR_SCREEN_ON,
    };
    assert(!memcmp(buf, expected, sizeof(expected)));
}