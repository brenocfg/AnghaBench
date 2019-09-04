#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int count_lhs; scalar_t__ count_rhs; int /*<<< orphan*/  protid; } ;
typedef  TYPE_1__ twr_empty_floor_t ;
struct connection_ops {size_t (* get_top_of_tower ) (unsigned char*,char const*,char const*) ;int /*<<< orphan*/ * epm_protocols; } ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EPT_S_NOT_REGISTERED ; 
 int /*<<< orphan*/  RPC_S_INVALID_RPC_PROTSEQ ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 struct connection_ops* rpcrt4_get_conn_protseq_ops (char const*) ; 
 size_t stub1 (unsigned char*,char const*,char const*) ; 
 size_t stub2 (unsigned char*,char const*,char const*) ; 

RPC_STATUS RpcTransport_GetTopOfTower(unsigned char *tower_data,
                                      size_t *tower_size,
                                      const char *protseq,
                                      const char *networkaddr,
                                      const char *endpoint)
{
    twr_empty_floor_t *protocol_floor;
    const struct connection_ops *protseq_ops = rpcrt4_get_conn_protseq_ops(protseq);

    *tower_size = 0;

    if (!protseq_ops)
        return RPC_S_INVALID_RPC_PROTSEQ;

    if (!tower_data)
    {
        *tower_size = sizeof(*protocol_floor);
        *tower_size += protseq_ops->get_top_of_tower(NULL, networkaddr, endpoint);
        return RPC_S_OK;
    }

    protocol_floor = (twr_empty_floor_t *)tower_data;
    protocol_floor->count_lhs = sizeof(protocol_floor->protid);
    protocol_floor->protid = protseq_ops->epm_protocols[0];
    protocol_floor->count_rhs = 0;

    tower_data += sizeof(*protocol_floor);

    *tower_size = protseq_ops->get_top_of_tower(tower_data, networkaddr, endpoint);
    if (!*tower_size)
        return EPT_S_NOT_REGISTERED;

    *tower_size += sizeof(*protocol_floor);

    return RPC_S_OK;
}