#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  public_key; } ;
struct TYPE_6__ {unsigned int connections_length; } ;
typedef  TYPE_1__ TCP_Connections ;
typedef  TYPE_2__ TCP_Connection_to ;

/* Variables and functions */
 TYPE_2__* get_connection (TYPE_1__*,unsigned int) ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int find_tcp_connection_to(TCP_Connections *tcp_c, const uint8_t *public_key)
{
    unsigned int i;

    for (i = 0; i < tcp_c->connections_length; ++i) {
        TCP_Connection_to *con_to = get_connection(tcp_c, i);

        if (con_to) {
            if (public_key_cmp(con_to->public_key, public_key) == 0) {
                return i;
            }
        }
    }

    return -1;
}