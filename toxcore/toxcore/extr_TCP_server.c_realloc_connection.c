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
typedef  int uint32_t ;
struct TYPE_3__ {int size_accepted_connections; int /*<<< orphan*/ * accepted_connection_array; } ;
typedef  TYPE_1__ TCP_Server ;
typedef  int /*<<< orphan*/  TCP_Secure_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int realloc_connection(TCP_Server *TCP_server, uint32_t num)
{
    if (num == 0) {
        free(TCP_server->accepted_connection_array);
        TCP_server->accepted_connection_array = NULL;
        TCP_server->size_accepted_connections = 0;
        return 0;
    }

    if (num == TCP_server->size_accepted_connections) {
        return 0;
    }

    TCP_Secure_Connection *new_connections = realloc(TCP_server->accepted_connection_array,
            num * sizeof(TCP_Secure_Connection));

    if (new_connections == NULL)
        return -1;

    if (num > TCP_server->size_accepted_connections) {
        uint32_t old_size = TCP_server->size_accepted_connections;
        uint32_t size_new_entries = (num - old_size) * sizeof(TCP_Secure_Connection);
        memset(new_connections + old_size, 0, size_new_entries);
    }

    TCP_server->accepted_connection_array = new_connections;
    TCP_server->size_accepted_connections = num;
    return 0;
}