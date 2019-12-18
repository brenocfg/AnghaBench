#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ TCP_Client_Connection ;

/* Variables and functions */
 int read_TCP_packet (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int socks5_read_handshake_response(TCP_Client_Connection *TCP_conn)
{
    uint8_t data[2];
    int ret = read_TCP_packet(TCP_conn->sock, data, sizeof(data));

    if (ret == -1)
        return 0;

    if (data[0] == 5 && data[1] == 0) // FIXME magic numbers
        return 1;

    return -1;
}