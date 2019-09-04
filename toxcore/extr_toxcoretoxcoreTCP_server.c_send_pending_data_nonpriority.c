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
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ last_packet_length; int last_packet_sent; int last_packet; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ TCP_Secure_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int send (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_pending_data_nonpriority(TCP_Secure_Connection *con)
{
    if (con->last_packet_length == 0) {
        return 0;
    }

    uint16_t left = con->last_packet_length - con->last_packet_sent;
    int len = send(con->sock, con->last_packet + con->last_packet_sent, left, MSG_NOSIGNAL);

    if (len <= 0)
        return -1;

    if (len == left) {
        con->last_packet_length = 0;
        con->last_packet_sent = 0;
        return 0;
    }

    con->last_packet_sent += len;
    return -1;

}