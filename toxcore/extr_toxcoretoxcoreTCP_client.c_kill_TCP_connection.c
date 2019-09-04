#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sock; int /*<<< orphan*/  priority_queue_start; } ;
typedef  TYPE_1__ TCP_Client_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kill_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sodium_memzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wipe_priority_list (int /*<<< orphan*/ ) ; 

void kill_TCP_connection(TCP_Client_Connection *TCP_connection)
{
    if (TCP_connection == NULL)
        return;

    wipe_priority_list(TCP_connection->priority_queue_start);
    kill_sock(TCP_connection->sock);
    sodium_memzero(TCP_connection, sizeof(TCP_Client_Connection));
    free(TCP_connection);
}