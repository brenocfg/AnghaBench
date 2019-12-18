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
typedef  int /*<<< orphan*/  SocketType ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_FIFO ; 
 int /*<<< orphan*/  SOCKET_MQUEUE ; 
 int /*<<< orphan*/  SOCKET_SOCKET ; 
 int /*<<< orphan*/  SOCKET_SPECIAL ; 
 int /*<<< orphan*/  SOCKET_USB_FUNCTION ; 
 scalar_t__ STR_IN_SET (char const*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  _SOCKET_TYPE_INVALID ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

SocketType socket_port_type_from_string(const char *s) {
        assert(s);

        if (STR_IN_SET(s, "Stream", "Datagram", "SequentialPacket", "Netlink"))
                return SOCKET_SOCKET;
        else if (streq(s, "Special"))
                return SOCKET_SPECIAL;
        else if (streq(s, "MessageQueue"))
                return SOCKET_MQUEUE;
        else if (streq(s, "FIFO"))
                return SOCKET_FIFO;
        else if (streq(s, "USBFunction"))
                return SOCKET_USB_FUNCTION;
        else
                return _SOCKET_TYPE_INVALID;
}