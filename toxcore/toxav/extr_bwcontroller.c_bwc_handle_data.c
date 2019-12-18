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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct BWCMessage {int dummy; } ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int on_update (void*,struct BWCMessage*) ; 

int bwc_handle_data(Messenger *m, uint32_t friendnumber, const uint8_t *data, uint16_t length, void *object)
{
    if (length - 1 != sizeof(struct BWCMessage))
        return -1;

    /* NOTE the data is mutable */
    return on_update(object, (struct BWCMessage *) (data + 1));
}