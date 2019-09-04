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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  TCP_Server ;
typedef  int /*<<< orphan*/  TCP_Secure_Connection ;

/* Variables and functions */
 int add_accepted (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int handle_TCP_packet (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_TCP_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_accepted (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sodium_memzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int confirm_TCP_connection(TCP_Server *TCP_server, TCP_Secure_Connection *con, const uint8_t *data,
                                  uint16_t length)
{
    int index = add_accepted(TCP_server, con);

    if (index == -1) {
        kill_TCP_connection(con);
        return -1;
    }

    sodium_memzero(con, sizeof(TCP_Secure_Connection));

    if (handle_TCP_packet(TCP_server, index, data, length) == -1) {
        kill_accepted(TCP_server, index);
        return -1;
    }

    return index;
}