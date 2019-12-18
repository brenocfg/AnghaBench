#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {scalar_t__ status; scalar_t__ ping_id; int /*<<< orphan*/  last_pinged; scalar_t__ identifier; } ;
struct TYPE_11__ {int /*<<< orphan*/  public_key; } ;
struct TYPE_10__ {int size_accepted_connections; int num_accepted_connections; TYPE_4__* accepted_connection_array; scalar_t__ counter; int /*<<< orphan*/  accepted_key_list; } ;
typedef  TYPE_1__ TCP_Server ;
typedef  TYPE_2__ TCP_Secure_Connection ;

/* Variables and functions */
 scalar_t__ TCP_STATUS_CONFIRMED ; 
 scalar_t__ TCP_STATUS_NO_STATUS ; 
 int /*<<< orphan*/  bs_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int get_TCP_connection_index (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_accepted (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_2__ const*,int) ; 
 int realloc_connection (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unix_time () ; 

__attribute__((used)) static int add_accepted(TCP_Server *TCP_server, const TCP_Secure_Connection *con)
{
    int index = get_TCP_connection_index(TCP_server, con->public_key);

    if (index != -1) { /* If an old connection to the same public key exists, kill it. */
        kill_accepted(TCP_server, index);
        index = -1;
    }

    if (TCP_server->size_accepted_connections == TCP_server->num_accepted_connections) {
        if (realloc_connection(TCP_server, TCP_server->size_accepted_connections + 4) == -1)
            return -1;

        index = TCP_server->num_accepted_connections;
    } else {
        uint32_t i;

        for (i = TCP_server->size_accepted_connections; i != 0; --i) {
            if (TCP_server->accepted_connection_array[i - 1].status == TCP_STATUS_NO_STATUS) {
                index = i - 1;
                break;
            }
        }
    }

    if (index == -1) {
        fprintf(stderr, "FAIL index is -1\n");
        return -1;
    }

    if (!bs_list_add(&TCP_server->accepted_key_list, con->public_key, index))
        return -1;

    memcpy(&TCP_server->accepted_connection_array[index], con, sizeof(TCP_Secure_Connection));
    TCP_server->accepted_connection_array[index].status = TCP_STATUS_CONFIRMED;
    ++TCP_server->num_accepted_connections;
    TCP_server->accepted_connection_array[index].identifier = ++TCP_server->counter;
    TCP_server->accepted_connection_array[index].last_pinged = unix_time();
    TCP_server->accepted_connection_array[index].ping_id = 0;

    return index;
}